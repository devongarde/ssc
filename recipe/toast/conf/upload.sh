#!/bin/sh

# this is the script I run under macos to check and upload a website
# (prepared by ssc using corrupt.conf or live.conf). It uses rsync.


upload_using_rsync () {
# 1. source directory
# 2. destination server
# 3. if 1, force upload all, otherwise only newer files

  if [[ $3 -gt 0 ]] ; then
    FLAGS=-rmpt4
  else
    FLAGS=-rumpt4
  fi

  rsync $FLAGS --inplace --delete-after --chmod=Fu+w --exclude='\.*' -e ssh $1 $2
}


upload_to_server () {
# 1. local source directory
# 2. server destination directory
# 3. if 1, copy all
# 4. destination server
# 5. destination user

  echo "Uploading..."
  upload_using_rsync "$1/*" "$5@$4:$2" $3
  # reinforce permissions
  ssh "$5@$4" "find "$2" -type d ! -perm 755 -exec chmod 755 {} \;"
  ssh "$5@$4" "find "$2" -type f ! -perm 644 -exec chmod 644 {} \;"
}


aid () {
  echo "upload.sh SHADOW SERVER TARGET USER ALL"
  echo "SHADOW: the source (ssc shadow) directory"
  echo "SERVER: the target server name"
  echo "TARGET: the target server's destination directory"
  echo "USER:   the target server's ssh user"
  echo "ALL:    if 'all', copy all files, otherwise only copy changes"
}


verify () {
# 1. local source directory
# 2. server destination directory
# 3. destination server
# 4. destination user
# 5. if 1, copy all

  if [[ "$4" == "" ]] ; then
    aid
    exit
  fi

  if [[ "$6" != "" ]] ; then
    aid
    exit
  fi

if [[ ! -d "$1" ]] ; then
    echo "Cannot find $1, or it is not a directory"
    exit
  fi

  if [[ "$5" == "all" ]] ; then
    upload_to_server "$1" "$2" 1 "$3" "$4"
  else
    upload_to_server "$1" "$2" 0 "$3" "$4"
  fi

  echo "Done."
}


verify $@
