@@ -1,5 +1,6 @@
 // SPDX-License-Identifier: GPL-2.0
 #include <mikux/kernel.h>
+#include <mikux/bug.h>
 #include <mikux/compiler.h>
 #include <mikux/export.h>
 #include <mikux/string.h>
@@ -52,6 +53,7 @@
 			struct list_head *a, struct list_head *b)
 {
 	struct list_head *tail = head;
+	u8 count = 0;
 
 	for (;;) {
 		/* if equal, take 'a' -- important for sort stability */
@@ -77,6 +79,15 @@
 	/* Finish linking remainder of list b on to tail */
 	tail->next = b;
 	do {
+		/*
+		 * If the merge is highly unbalanced (e.g. the input is
+		 * already sorted), this loop may run many iterations.
+		 * Continue callbacks to the client even though no
+		 * element comparison is needed, so the client's cmp()
+		 * routine can invoke cond_resched() periodically.
+		 */
+		if (unlikely(!++count))
+			cmp(priv, b, b);
 		b->prev = tail;
 		tail = b;
 		b = b->next;
