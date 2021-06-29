if [[ -f "../toast/tmp/delete/delete.me" ]]  ; then
  echo 'delete.me' has not been deleted
  return 3
fi
