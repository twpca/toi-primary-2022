FROM debian:buster

RUN sed -i.bak -e "s%http://deb.debian.org/debian%http://ftp.jp.debian.org/debian%g" /etc/apt/sources.list
RUN apt-get update
RUN apt-get install -y curl wget perl lmodern gnupg2 python3 python3-pip python3-distutils libfontconfig1
RUN pip3 install toml

# texlive
RUN wget http://ftp.jaist.ac.jp/pub/CTAN/systems/texlive/tlnet/install-tl-unx.tar.gz && \
    tar xzf install-tl-unx.tar.gz && \
    cd install-tl-* && \
    printf "%s\n" \
        "selected_scheme scheme-basic" \
        "tlpdbopt_install_docfiles 0" \
        "tlpdbopt_install_srcfiles 0" \
        > texlive.profile && \
    ./install-tl --profile=texlive.profile \
        --repository http://ftp.jaist.ac.jp/pub/CTAN/systems/texlive/tlnet/ && \
    cd .. && rm -rf install-tl-* install-tl-unx.tar.gz
ENV PATH "$PATH:/usr/local/texlive/2021/bin/x86_64-linux"

# packages
RUN curl -fsSL https://www.preining.info/rsa.asc | tlmgr key add -
RUN tlmgr init-usertree
RUN tlmgr update --self --all
RUN tlmgr repository add http://contrib.texlive.info/current tlcontrib
RUN tlmgr pinning add tlcontrib '*'
RUN tlmgr install collection-basic collection-fontsrecommended collection-fontutils \
    collection-langcjk collection-langjapanese collection-langchinese \
    collection-latexrecommended collection-luatex libertine titlesec lipsum titling \
    needspace amsmath makecell \
    babel-russian

# fonts
RUN mkdir -p /usr/local/texlive/texmf-local/fonts/opentype/adobe/sourcehanserif/
RUN mkdir -p /usr/local/texlive/texmf-local/fonts/opentype/adobe/sourcehansans/
RUN mkdir -p /usr/local/texlive/texmf-local/fonts/opentype/adobe/sourcehan-otc/
COPY font/serif/* /usr/local/texlive/texmf-local/fonts/opentype/adobe/sourcehanserif/
COPY font/sans/* /usr/local/texlive/texmf-local/fonts/opentype/adobe/sourcehansans/
COPY font/otc/* /usr/local/texlive/texmf-local/fonts/opentype/adobe/sourcehan-otc/
RUN mktexlsr
RUN kanji-config-updmap-sys status

# pandoc
RUN wget https://github.com/jgm/pandoc/releases/download/2.16.1/pandoc-2.16.1-1-amd64.deb && \
    dpkg -i pandoc-2.16.1-1-amd64.deb && \
    rm pandoc-2.16.1-1-amd64.deb

# dummy compile to speed up future builds
RUN mkdir -p /tmp/compile
COPY dummy.tex /tmp/compile
RUN cd /tmp/compile && \
    lualatex -halt-on-error dummy.tex && \
    lualatex -halt-on-error dummy.tex && \
    cd / && \
    rm -rf /tmp/compile

VOLUME /workdir
WORKDIR /workdir
