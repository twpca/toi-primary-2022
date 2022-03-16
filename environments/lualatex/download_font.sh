#/usr/bin/bash

curl -LO "https://github.com/adobe-fonts/source-han-sans/archive/2.004R.tar.gz"
curl -LO "https://github.com/adobe-fonts/source-han-serif/archive/2.000R.tar.gz"

mkdir -p font/otc
mkdir -p font/sans
mkdir -p font/serif

tar zxvf 2.004R.tar.gz -C font/otc --wildcards 'source-han-sans-2.004R/OTC/*.ttc' --transform='s/.*\///'
tar zxvf 2.004R.tar.gz -C font/sans --wildcards 'source-han-sans-2.004R/OTF/Japanese/*.otf' --transform='s/.*\///'
tar zxvf 2.004R.tar.gz -C font/sans --wildcards 'source-han-sans-2.004R/OTF/TraditionalChinese/*.otf' --transform='s/.*\///'

tar zxvf 2.000R.tar.gz -C font/otc --wildcards 'source-han-serif-2.000R/OTC/*.ttc' --transform='s/.*\///'
tar zxvf 2.000R.tar.gz -C font/serif --wildcards 'source-han-serif-2.000R/OTF/Japanese/*.otf' --transform='s/.*\///'
tar zxvf 2.000R.tar.gz -C font/serif --wildcards 'source-han-serif-2.000R/OTF/TraditionalChinese/*.otf' --transform='s/.*\///'

rm 2.000R.tar.gz 2.004R.tar.gz
