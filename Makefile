# Makefile for libicpc.pdf
LATEX = platex
LATEXFLAGS = 
DVIPDFM = dvipdfmx
DVIPDFMFLAGS = -p a4
EBB = ebb
TARGET = libicpc
TEXFILES := $(wildcard section/*.tex)

all: $(TARGET).pdf

$(TARGET).pdf : $(TARGET).dvi
	$(DVIPDFM) $(DVIPDFMFLAGS) $<

$(TARGET).dvi : $(TARGET).tex $(TEXFILES)
	$(LATEX) $(LATEXFLAGS) $<
	$(LATEX) $(LATEXFLAGS) $<


.PHONY : clean
clean:
	rm -f *.log *.dvi *.snm *.toc *.aux *.out *.nav
