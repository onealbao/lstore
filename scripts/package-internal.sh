#!/bin/bash

#
#  package-internal.sh - Runs within docker container to package LStore
#

#
# Preliminary bootstrapping
#
set -eu
ABSOLUTE_PATH=$(cd `dirname "${BASH_SOURCE[0]}"` && pwd)
source $ABSOLUTE_PATH/functions.sh
PACKAGE_DISTRO=${1:-unknown_distro}
PACKAGE_SUBDIR=$PACKAGE_DISTRO

# todo could probe this from docker variables
PACKAGE_BASE="/tmp/lstore-release"
SOURCE_BASE=$LSTORE_RELEASE_BASE/source
REPO_BASE=$LSTORE_RELEASE_BASE/repo/$PACKAGE_SUBDIR
# Here and elsewhere, we need to set the umask when we write to the host-mounted
#    paths. Otherwise users outside the container can't read/write files. But,
#    we don't want to just blindly set umask 0000, in case there's some
#    weirdness with how the installer works.
(
    umask 000
    mkdir -p $PACKAGE_BASE/{build,cmake} $REPO_BASE
    # That being said, umask appears to not work right...
    # FIXME: Why is umask so sad?
    chmod 777 $PACKAGE_BASE $PACKAGE_BASE/{build,cmake} $REPO_BASE
)
check_cmake $PACKAGE_BASE/cmake
note "Beginning packaging at $(date) for $PACKAGE_SUBDIR"

#
# Get weird. Build each package, then install the RPM. If this is 
#   configurable in the future, the order of packages matters.
#
cd $PACKAGE_BASE/build
for PACKAGE in apr-accre apr-util-accre jerasure toolbox gop ibp lio; do
    (
        umask 000
        mkdir -p $PACKAGE
        # See above.
        chmod 777 $PACKAGE
    )
    pushd $PACKAGE
    # NOTE: Can't do this with --git-dir. Git 1.8.3.1 considers the tag "dirty"
    #       if the CURRENT working directory is dirty...
    TAG_NAME=$(cd $SOURCE_BASE/$PACKAGE/ && \
               git describe --abbrev=32 --dirty --candidates=100 \
               --match 'ACCRE_*' | sed 's,^ACCRE_,,')
    PACKAGE_REPO=$REPO_BASE/$PACKAGE/$TAG_NAME
    if [ ! -e $PACKAGE_REPO ]; then
        set -x
        build_lstore_package $PACKAGE $SOURCE_BASE/$PACKAGE $TAG_NAME \
                             $PACKAGE_DISTRO
        mkdir -p $PACKAGE_REPO
        # Need to figure out what to do with these eventually.
        rm *.source.rpm || true
        (
            umask 000
            # Obviously needs to be changed to handle .deb
            cp *.rpm $PACKAGE_REPO
            chmod 666 $PACKAGE_REPO/*
        )
        set +x 
    else
        note "Tag $TAG_NAME of $PACKAGE already exists in:"
        note "    ${PACKAGE_REPO}"
        note "    Instead of building, we are installing from there."
    fi
    rpm -i $REPO_BASE/$PACKAGE/$TAG_NAME/*.rpm
    popd 
done