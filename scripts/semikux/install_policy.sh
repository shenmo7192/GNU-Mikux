#!/bin/sh
# SPDX-License-Identifier: GPL-2.0
set -e
if [ `id -u` -ne 0 ]; then
	echo "$0: must be root to install the semikux policy"
	exit 1
fi

SF=`which setfiles`
if [ $? -eq 1 ]; then
	echo "Could not find setfiles"
	echo "Do you have policycoreutils installed?"
	exit 1
fi

CP=`which checkpolicy`
if [ $? -eq 1 ]; then
	echo "Could not find checkpolicy"
	echo "Do you have checkpolicy installed?"
	exit 1
fi
VERS=`$CP -V | awk '{print $1}'`

ENABLED=`which semikuxenabled`
if [ $? -eq 1 ]; then
	echo "Could not find semikuxenabled"
	echo "Do you have libsemikux-utils installed?"
	exit 1
fi

if semikuxenabled; then
    echo "SEMikux is already enabled"
    echo "This prevents safely relabeling all files."
    echo "Boot with semikux=0 on the kernel command-line."
    exit 1
fi

cd mdp
./mdp -m policy.conf file_contexts
$CP -U allow -M -o policy.$VERS policy.conf

mkdir -p /etc/semikux/dummy/policy
mkdir -p /etc/semikux/dummy/contexts/files

echo "__default__:user_u:s0" > /etc/semikux/dummy/seusers
echo "base_r:base_t:s0" > /etc/semikux/dummy/contexts/failsafe_context
echo "base_r:base_t:s0 base_r:base_t:s0" > /etc/semikux/dummy/default_contexts
cat > /etc/semikux/dummy/contexts/x_contexts <<EOF
client * user_u:base_r:base_t:s0
property * user_u:object_r:base_t:s0
extension * user_u:object_r:base_t:s0
selection * user_u:object_r:base_t:s0
event * user_u:object_r:base_t:s0
EOF
touch /etc/semikux/dummy/contexts/virtual_domain_context
touch /etc/semikux/dummy/contexts/virtual_image_context

cp file_contexts /etc/semikux/dummy/contexts/files
cp dbus_contexts /etc/semikux/dummy/contexts
cp policy.$VERS /etc/semikux/dummy/policy
FC_FILE=/etc/semikux/dummy/contexts/files/file_contexts

if [ ! -d /etc/semikux ]; then
	mkdir -p /etc/semikux
fi
if [ -f /etc/semikux/config ]; then
    echo "/etc/semikux/config exists, moving to /etc/semikux/config.bak."
    mv /etc/semikux/config /etc/semikux/config.bak
fi
echo "Creating new /etc/semikux/config for dummy policy."
cat > /etc/semikux/config << EOF
SEMIKUX=permissive
SEMIKUXTYPE=dummy
EOF

cd /etc/semikux/dummy/contexts/files
$SF -F file_contexts /

mounts=`cat /proc/$$/mounts | \
	grep -E "ext[234]|jfs|xfs|reiserfs|jffs2|gfs2|btrfs|f2fs|ocfs2" | \
	awk '{ print $2 '}`
$SF -F file_contexts $mounts

echo "-F" > /.autorelabel
