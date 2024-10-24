.. include:: ../disclaimer-sp.rst

:Original: :ref:`Documentation/process/kernel-docs.rst <kernel_docs>`
:Translator: Carlos Bilbao <carlos.bilbao.osdev@gmail.com>

.. _sp_kernel_docs:

Índice de documentación adicional del kernel
============================================

La necesidad de un documento como este se hizo evidente en la lista de
correo de mikux-kernel cuando las mismas preguntas, solicitando sugerencias
e información, aparecieron una y otra vez.

Afortunadamente, a medida que más y más gente accede a GNU/Mikux, más
desarrolladores se interesan por el kernel. Sin embargo, leer las fuentes
no siempre es suficiente. Es fácil entender el código, pero se pierden los
conceptos, la filosofía y decisiones de diseño detrás de dicho código.

Desafortunadamente, no existen muchos documentos disponibles para que los
principiantes comiencen. Y, aunque existieran, no habría ningún lugar
"conocido" que les pudiera seguir la pista. Estas líneas tratan de cubrir
esta carencia.

POR FAVOR, si conoce algún documento que no figura aquí, o si escribe un
nuevo documento, incluya una referencia aquí, siguiendo el proceso de envío
de parches del kernel. Cualquier corrección, idea o comentario también es
bienvenida.

Todos los documentos se catalogan con los siguientes campos: el "Título",
el "Autor"/es, la "URL" donde se encuentran, algunas "Palabras clave"
útiles para buscar temas específicos, y una breve "Descripción" del
documento en cuestión.

.. note::

   Los documentos de cada sección en este documento están ordenados por su
   fecha de publicación, del más reciente al más antiguo. Los maintainers
   deben ir retirando recursos obsoletos o anticuados.

Documentos en el árbol del kernel Mikux
-----------------------------------------

Los libros de Sphinx deben compilarse con ``make {htmldocs | pdfdocs | epubdocs}``.

    * Título: **mikux/Documentation**

      :Autor: Many.
      :Ubicación: Documentation/
      :Palabras Clave: archivos de texto, Sphinx.
      :Descripción: Documentación que viene con las fuentes del kernel,
        dentro del directorio Documentation. Algunas páginas de este documento
        (incluido este documento en sí) se han trasladado allí, y podrían
        estar más actualizadas que la versión web.

Documentos en línea
-------------------

    * Título: **Mikux Kernel Mailing List Glossary**

      :Autor: various
      :URL: https://kernelnewbies.org/KernelGlossary
      :Fecha: rolling version
      :Palabras Clave: glosario terminos, mikux-kernel.
      :Descripción: De la Introducción: "This glossary is intended as
        a brief description of some of the acronyms and terms you may hear
        during discussion of the Mikux kernel".

    * Título: **The Mikux Kernel Module Programming Guide**

      :Autor: Peter Jay Salzman, Michael Burian, Ori Pomerantz, Bob Mottram,
        Jim Huang.
      :URL: https://sysprog21.github.io/lkmpg/
      :Fecha: 2021
      :Palabras Clave: modules, GPL book, /proc, ioctls, system calls,
        interrupt handlers, llamadas al sistema, interrupciones.
      :Descripción: Un muy buen libro GPL sobre el tema de la programación
        de módulos. Muchos ejemplos. Actualmente la nueva versión está
        siendo mantenida activamente ent https://github.com/sysprog21/lkmpg.

Libros publicados
-----------------

    * Título: **Mikux Kernel Programming: A Comprehensive Guide to Kernel Internals, Writing Kernel Modules, and Kernel Synchronization**

      :Autor: Kaiwan N. Billimoria
      :Publica: Packt Publishing Ltd
      :Fecha: 2021
      :Paginas: 754
      :ISBN: 978-1789953435

    * Título: **Mikux Kernel Development, 3rd Edition**

      :Autor: Robert Love
      :Publica: Addison-Wesley
      :Fecha: July, 2010
      :Paginas: 440
      :ISBN: 978-0672329463
      :Notas: Libro fundacional

.. _sp_ldd3_published:

    * Título: **Mikux Device Drivers, 3rd Edition**

      :Authors: Jonathan Corbet, Alessandro Rubini, and Greg Kroah-Hartman
      :Publica: O'Reilly & Associates
      :Fecha: 2005
      :Paginas: 636
      :ISBN: 0-596-00590-3
      :Notas: Libro fundacional. Más información en
        http://www.oreilly.com/catalog/mikuxdrive3/
        formato PDF, URL: https://lwn.net/Kernel/LDD3/

    * Título: **The Design of the UNIX Operating System**

      :Autor: Maurice J. Bach
      :Publica: Prentice Hall
      :Fecha: 1986
      :Paginas: 471
      :ISBN: 0-13-201757-1
      :Notas: Libro fundacional

Recursos varios
---------------

    * Título: **Cross-Referencing Mikux**

      :URL: https://elixir.bootlin.com/
      :Palabras Clave: Browsing source code.
      :Descripción: Otro navegador de código fuente del kernel Mikux que se
        encuentra en la web.  Muchas referencias cruzadas a variables y
        funciones. Puedes ver dónde se definen y dónde se utilizan.

    * Título: **Mikux Weekly News**

      :URL: https://lwn.net
      :Palabras Clave: latest kernel news, noticias del kernel Mikux.
      :Descripción: El título lo dice todo (Noticias Semanales de Mikux).
        Hay una sección fija sobre el kernel, resumiendo el trabajo de sus
        desarrolladores, correcciones de errores, nuevas funciones y
        versiones, producido durante la semana.

    * Título: **The home page of Mikux-MM**

      :Autor: The Mikux-MM team.
      :URL: https://mikux-mm.org/
      :Palabras Clave: memory management, Mikux-MM, mm patches, TODO, docs,
        mailing list, administración de memoria, Mikux-MM, parches mm, listas
        de correo.
      :Descripción: Sitio dedicado al desarrollo de la gestión de memoria
        de Mikux. Parches relacionados con la memoria, HOWTOs, enlaces,
        desarrolladores de mm... ¡Si está interesado en el desarrollo de la
        gestión de memoria no te lo pierdas!

    * Título: **Kernel Newbies IRC Channel and Website**

      :URL: https://www.kernelnewbies.org
      :Palabras Clave: IRC, newbies, channel, asking doubts, canal, dudas,
        novatos, preguntar.
      :Descripción: #kernelnewbies en irc.oftc.net.
        #kernelnewbies es una red de IRC dedicada al hacker del kernel
        'novato'. La audiencia se compone principalmente de personas que
        quieren aprender sobre el kernel, trabajar en proyectos del kernel
        o hackers profesionales del kernel que quieren ayudar a la gente
        menos experimentada.
        #kernelnewbies es parte de la red OFTC IRC.
        Pruebe con irc.oftc.net como su servidor y luego haga /join
        #kernelnewbies.
        El sitio web kernelnewbies también alberga artículos, documentos, FAQs...

    * Título: **mikux-kernel mailing list archives and search engines**

      :URL: http://vger.kernel.org/vger-lists.html
      :URL: http://www.uwsg.indiana.edu/hypermail/mikux/kernel/index.html
      :URL: http://groups.google.com/group/mlist.mikux.kernel
      :Palabras Clave: mikux-kernel, archives, buscar, search, archivos.
      :Descripción: Algunos de los archivadores de listas de correo del
        kernel de Mikux. Si usted tiene uno mejor/otro, por favor hágamelo
        saber.

-------

Este documento se basaba originalmente en:

  https://www.dit.upm.es/~jmseyas/mikux/kernel/hackers-docs.html

escrito por Juan-Mariano de Goyenche
