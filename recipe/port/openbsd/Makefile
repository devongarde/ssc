COMMENT=        opinionated static (web)site nitpicker

V=              0.1.52
DISTNAME=       ssc-v$V
PKGNAME=        ssc-$V

CATEGORIES=     www
HOMEPAGE=       https://ssc.lu/
MAINTAINER=     Dylan Harris <mail@dylanharris.org>

# GPLv3 only
PERMIT_PACKAGE= yes

SITES=          https://ssc.lu/src/
EXTRACT_SUFX=   .tgz

COMPILER=       base-clang \
                ports-gcc
ONLY_FOR_ARCHS= amd64 \
                arm64

WANTLIB +=      boost_atomic-mt boost_chrono-mt boost_date_time-mt
WANTLIB +=      boost_filesystem-mt boost_json-mt boost_locale-mt
WANTLIB +=      boost_program_options-mt boost_regex-mt boost_system-mt
WANTLIB +=      boost_thread-mt c curl hunspell-1.7 icudata icui18n
WANTLIB +=      icuio icutu icuuc m pthread
WANTLIB +=      ${COMPILER_LIBCXX}

MODULES=        devel/cmake
BUILD_DEPENDS=  devel/microsoft-gsl
LIB_DEPENDS=    devel/boost \
                net/curl \
                textproc/hunspell \
                textproc/icu4c

.include <bsd.port.mk>
