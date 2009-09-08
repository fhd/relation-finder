RM=rm -f
CP=cp -p

all:
	$(MAKE) -C qwbd
	$(MAKE) -C qwbdc
	$(MAKE) -C qcreate
	$(CP) qwbd/qwbd ..
	$(CP) qwbdc/qwbdc ..
	$(CP) qcreate/qcreate ..

clean:
	$(MAKE) clean -C qwbd
	$(MAKE) clean -C qwbdc
	$(MAKE) clean -C qcreate
	$(RM) qwbd/qwbd ../qwbd
	$(RM) qwbdc/qwbdc ../qwbdc
	$(RM) qcreate/qcreate ../qcreate
