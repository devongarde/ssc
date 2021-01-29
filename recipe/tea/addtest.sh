#!/bin/sh
#

# add tests to toast directory

# parameters
# 1. test set (e.g. living), see toast
# 0. for jan, 7 for jul
# 3. first year (by number)
# 4. test file name
# 5. file containing snippet to add to end of .spec

function dohelp {
  echo "ADDTEST set month year testfile specsnippetfile specfile"
  echo "set is directory under toast"
  echo "month is first month, 0 or 7"
  echo "year is first two digit year"
  echo "testfile should be obvious"
  echo "specsnippetfile is .spec to be added to end of specfile"
  echo "specfile is spec file in all target directories"
}

if [[ "$6" == "" ]] ; then
    dohelp ()
    exit 3
fi

if [[ ! -e "$5" ]] ; then
  echo "cannot access $5"
  exit 3
fi

if [[ ! -e "$4" ]] ; then
  echo "cannot access $5"
  exit 3
fi

if [[ $2 == 7 ]] ; then
  EXCLUDE=jan$3
elif [[ $2 != 0 ]] ; then
  echo "month must be 0 or 7"
  exit 3
fi

if [[ ! -d "$1/jul$3" && ! -d "$1/jan$3" ]] ; then
  echo "can find neither $1/jan$3 nor $1/jul$3"
  exit 3
fi

