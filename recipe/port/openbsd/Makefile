COMMENT=        opinionated static (web)site nitpicker

V=              0.1.24
DISTNAME=       ssc-v$V
PKGNAME=        ssc-$V

CATEGORIES=     www
HOMEPAGE=       https://ssc.lu/
MAINTAINER=     Dylan Harris <mail@dylanharris.org>

# GPLv3 only
PERMIT_PACKAGE= yes

MASTER_SITES=   https://ssc.lu/src/
EXTRACT_SUFX=   .tgz

COMPILER=       base-clang ports-gcc
ONLY_FOR_ARCHS= amd64

WANTLIB +=      icudata icui18n icuuc icuio icutu m c hunspell-1.7 pthread
WANTLIB +=      boost_date_time-mt boost_filesystem-mt boost_locale-mt
WANTLIB +=      boost_program_options-mt boost_regex-mt boost_system-mt
WANTLIB +=      boost_chrono-mt boost_thread-mt curl
WANTLIB +=      ${COMPILER_LIBCXX}

MODULES=        devel/cmake
BUILD_DEPENDS=  devel/microsoft-gsl
LIB_DEPENDS=    devel/boost textproc/icu4c textproc/hunspell net/curl

NO_TEST=        yes

.include <bsd.port.mk>