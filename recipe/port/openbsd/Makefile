COMMENT=        opinionated static (web)site nitpicker

V=              0.1.54
DISTNAME=       ssc-v$V
PKGNAME=        ssc-$V

CATEGORIES=     www
HOMEPAGE=       https://ssc.lu/
MAINTAINER=     Dylan Harris <mail@dylanharris.org>

# GPLv3 only
PERMIT_PACKAGE= yes

SITES=          https://github.com/devongarde/ssc/releases/download/v${V}-alpha/
SITES.alt=      https://ssc.lu/src/
EXTRACT_SUFX=   .tgz

COMPILER=       base-clang \
                ports-gcc
ONLY_FOR_ARCHS= amd64 \
                arm64

WANTLIB +=      boost_atomic-mt boost_chrono-mt boost_container-mt
WANTLIB +=      boost_date_time-mt boost_filesystem-mt boost_json-mt
WANTLIB +=      boost_locale-mt boost_program_options-mt boost_regex-mt
WANTLIB +=      boost_system-mt boost_thread-mt c curl hunspell-1.7
WANTLIB +=      icudata icui18n icuio icutu icuuc m pthread
WANTLIB +=      ${COMPILER_LIBCXX}

MODULES=        devel/cmake
BUILD_DEPENDS=  devel/microsoft-gsl
LIB_DEPENDS=    devel/boost \
                net/curl \
                textproc/hunspell \
                textproc/icu4c

.include <bsd.port.mk>
