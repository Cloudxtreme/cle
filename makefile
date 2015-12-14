all:
	@cd src; $(MAKE)

debug:
	@cd srd; $(MAKE) debug

clean:
	@$(RM) cle
