#include <iostream>
#include "MdlxData.h"

int main(int argc, char* argv[])
{
	vector<string> arguments(argv + 1, argv + argc);
	if (arguments.size() == 0) {
		cout << "Usage:"<<argv[0]<<" input [output}\n";
		return 0;
	}

	auto infile = arguments[0];
	auto innoext = infile.length()>4 ? infile.substr(0,infile.length()-4) : "";
	auto inext = infile.length()>4 ? infile.substr(infile.length()-4,4) : "";
	if (strcasecmp(inext.c_str(), ".mdx")!=0 && strcasecmp(inext.c_str(), ".mdl")!=0) {
		cout << "The input must be a .mdx/.mdl file.\n";
		return 1;
	}

	auto outfile = arguments.size()>1 ? arguments[1] : innoext+(strcasecmp(inext.c_str(), ".mdx")==0 ? ".mdl" : ".mdx");
	auto outext = outfile.length()>4 ? outfile.substr(outfile.length()-4,4) : "";
	if (strcasecmp(outext.c_str(), ".mdx")!=0 && strcasecmp(outext.c_str(), ".mdl")!=0) {
		cout << "The output must be a .mdx/.mdl file.\n";
		return 1;
	}

	MDLX mdlx;

	if (strcasecmp(inext.c_str(), outext.c_str())==0) {// simply copy infile to outfile
		ifstream instream(infile, std::ios::binary);
		ofstream outstream(outfile, std::ios::binary);
		outstream << instream.rdbuf();
		instream.close();
		outstream.close();
	} else if (strcasecmp(inext.c_str(), ".mdx")==0) {// mdx -> mdl
		ifstream instream(infile, std::ios::binary);
		mdlx.MdxRead(instream);
		instream.close();

		FILE *fp = fopen(outfile.c_str(), "w");
		if (fp != NULL) {
			mdlx.MdlWrite(fp);
			fclose(fp);
		}
	} else {// mdl -> mdx
		ifstream instream(infile);
		mdlx.MdlRead(instream);
		instream.close();
		ofstream outstream(outfile, std::ios::binary);
		mdlx.MdxWrite(outstream);
		outstream.close();
	}

	return 0;
}
