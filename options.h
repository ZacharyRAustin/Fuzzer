#ifndef OPTIONS_H
#define OPTIONS_H

int parseCommandLine(int argc, char** argv);

int seedGiven();
unsigned int getSeed();
int outputGiven();
char* getOutputFileName();
int templateGiven();
char* getTemplateFileName();


#endif