all:
	@cd src; $(MAKE)

debug:
	@cd srd; $(MAKE) debug

clean:
	@$(RM) cle

install:
	sudo mv cle /usr/local/bin/cle
	sudo cp completion/clec /etc/bash_completion.d/cle

remove:
	sudo rm /usr/local/bin/cle
	sudo rm /etc/bash_completion.d/cle
