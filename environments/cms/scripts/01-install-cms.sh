#!/bin/bash -ex

readonly user=${DEFAULT_USER-$(whoami)}

installCMS () {
  # TODO: Refactor this to be parametrizable
  readonly AS_USER=${1-$user}
  # https://github.com/cms-dev/cms/commit/d21dee81b5c0e2393650f98dd82987d46fd16a69s
  # supports python 3.8
  readonly CMS_REVISION=${2-d21dee81b5c0e2393650f98dd82987d46fd16a69}

  cd /home/${AS_USER}

  # Change to non root user, otherwise the "isolate" compilation won't work
  su "$AS_USER" -c 'git clone https://github.com/cms-dev/cms.git cms-src'

  cd /home/${AS_USER}/cms-src
  su "$AS_USER" -c "git checkout ${CMS_REVISION} && git submodule update --init"

  cd /home/${AS_USER}/cms-src
  pip3 install -r requirements.txt --ignore-installed PyYAML
  python3 prerequisites.py -y --cmsuser=$AS_USER install
  python3 setup.py install
}

installCMS "$@"
