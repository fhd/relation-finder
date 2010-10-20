RM=rm -f
CP=cp -p

all:
	$(MAKE) -C wbd
	$(MAKE) -C wbdc
	$(MAKE) -C qcreate
	$(CP) wbd/wbd ..
	$(CP) wbdc/wbdc ..
	$(CP) qcreate/qcreate ..

clean:
	$(MAKE) clean -C wbd
	$(MAKE) clean -C wbdc
	$(MAKE) clean -C qcreate
	$(RM) wbd/wbd ../wbd
	$(RM) wbdc/wbdc ../wbdc
	$(RM) qcreate/qcreate ../qcreate
