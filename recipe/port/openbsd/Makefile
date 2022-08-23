COMMENT = opinionated static (web)site nitpicker

V = v0.1.2
DISTNAME = ssc-$V
PKGNAME = ssc-$V

CATEGORIES = www
HOMEPAGE = https://ssc.lu/
MAINTAINER = Dylan Harris <mail@dylanharris.org>

PERMIT_PACKAGE = yes

MASTER_SITES = https://ssc.lu/src/
EXTRACT_SUFX = .tgz

COMPILER = base-clang ports-gcc
ONLY_FOR_ARCHS = amd64

SEPARATE_BUILD = yes

WANTLIB += icudata icui18n icuuc boost_date_time-mt
WANTLIB += boost_filesystem-mt boost_locale-mt boost_chrono-mt
WANTLIB += boost_program_options-mt boost_regex-mt
WANTLIB += boost_system-mt boost_thread-mt c hunspell-1.7 pthread
WANTLIB += ${COMPILER_LIBCXX}

MODULES = devel/cmake
BUILD_DEPENDS = devel/microsoft-gsl
LIB_DEPENDS = devel/boost textproc/icu4c textproc/hunspell
RUN_DEPENDS = net/curl

CONFIGURE_STYLE = cmake
WRKBUILD = ${WRKSRC}/recipe/tea
WRKCONF = ${WRKSRC}/recipe/tea

.include <bsd.port.mk>
