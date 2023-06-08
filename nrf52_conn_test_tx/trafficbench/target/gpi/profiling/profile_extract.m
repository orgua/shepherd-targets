%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

1;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [fLineHeader, testbed, setup, rounds, traceMap] = scanTraceFile(fileName)

	fLineHeader	= [];
	testbed 	= struct();
	setup		= struct();
	rounds		= [];
	traceMap	= [];

	f = fopen(fileName, "rb");

	fseek(f, 0, SEEK_END);
	len = ftell(f);
	fseek(f, 0, SEEK_SET);
	if (len > 100 * 1024^2)
		b = questdlg( ...
				[sprintf("File size is quite large (%d MB),\n", round(len / 1024^2))	...
				"processing may be slow and memory consuming.\nContinue?"], ...
				"Warning", "Cancel", "Ok", "Cancel");
		if (!strcmp(b, "Ok"))
			return;
		endif
	endif

	s = fread(f, [1, inf], "*char");
	fclose(f);

	% detect trace file format
	p = {"(\\d+)"; "[^\\n]*SETUP:([^\\n]*)"; "EXP ([^\\n]*)"};
	fmt = 1;
	if (1)
		% desktop, Cooja
		fLineHeader = @(s) ["\\S+\\s+ID:" s "\\s+"];
		s1 = regexp(s, [fLineHeader(p{1}) p{2}], "matches", "once");
	endif
	if (isempty(s1))
		% FlockLab
		fLineHeader = @(s) ["[.\\d]+,\\d+," s ",r,"];
		s1 = regexp(s, [fLineHeader(p{1}) p{2}], "matches", "once");
		if (isempty(s1))
			s1 = regexp(s, [fLineHeader(p{1}) p{3}], "matches", "once");
			if (!isempty(s1))
				fmt = 2;
			endif
		endif
	endif
	if (isempty(s1))
		% Indriya (preprocessed)
		fLineHeader = @(s) ["\\d+," s ","];
		s1 = regexp(s, [fLineHeader(p{1}) p{2}], "matches", "once");
	endif
	if (isempty(s1))
		error("unsupported trace file format\n");
	endif

	% detect nodes
	switch (fmt)
		case 1
			s1 = regexp(s, [fLineHeader("(?<id>\\d+)") "[^\n]*SETUP:(?<setup>[^\n]*)"], "names");
		case 2
			s1 = regexp(s, [fLineHeader("(?<id>\\d+)") "EXP(?<setup>[^\n]*)"], "names");
	endswitch
	nodes = sort(str2double({s1.id}));
	testbed.nodes = [1 : length(nodes); nodes]';
	testbed.area = [length(nodes) + 1, max(nodes) + 1];
	nodesMap = [];
	nodesMap(nodes) = 1 : length(nodes);

	% read setup (from first node)
	s1 = regexp(s1(1).setup, "(?<name>\\w+) ?= ?(?<value>[^, ]+)", "names");
	for i = 1 : length({s1.value})
		s1(i).value = eval(s1(i).value);
	endfor
	setup = cell2struct({s1.value}, {s1.name}, 2);
	if (!isfield(setup, "slots"))
		setup.slots = setup.roundLen;
	endif
	switch (fmt)
		case 1
			setup.fmtINFOS = "INFOS \\((?<round>\\d+)\\)";
		case 2
			setup.fmtINFOS = "RND (?<round>\\d+)";
	endswitch
	if (setup.nodes != length(nodes))
		warning("number of nodes is inconsistent (setup: %u, found: %u)\n", setup.nodes, length(nodes));
	endif

	% scan rounds and trace data areas
	traceMap = [];
	[s1,p] = regexp(s, [fLineHeader("(?<id>\\d+)") setup.fmtINFOS], "names", "start");
	for i = 1 : length(p)
		traceMap(nodesMap(str2double(s1(i).id)), str2double(s1(i).round)) = p(i) - 1;
	endfor

	rounds = 1 : columns(traceMap);
	if (!isempty(rounds))
		while (max(traceMap(:,rounds(1))) == 0)
			rounds(1) = [];
		endwhile
		traceMap(:, end+1) = len;
	endif

	% drop trace data since it may be large
	s = [];

endfunction

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

[fileName, path] = uigetfile({'*.log;*.txt;*.csv'}, 'Load log data');
if (!fileName)
	return;
endif
inFile = [path fileName];

[fileName, path] = uiputfile({'*.csv'}, 'Save profile data as', path);
if (!fileName)
	return;
endif
outFile = [path fileName];

[fLineHeader, testbed, setup, rounds, traceMap] = scanTraceFile(inFile);
if (isempty(fLineHeader))
	return;
endif

if (rows(testbed.nodes) > 1)
	[N, ok] = listdlg("ListString", cellstr(int2str(testbed.nodes(:,2))), "Name", "Select nodes to extract");
	if (!ok)
		return;
	endif
	nodes = N(:)';
else
	nodes = testbed.nodes(:,1)';
endif	

f = fopen(inFile, "rb");
s = fread(f, [1, inf], "*char");
fclose(f);

f = fopen(outFile, "w");

printf("processing profile data ..."); fflush(stdout);
for n = nodes
	for r = rounds

		if (!traceMap(n,r))
			continue;
		endif

		if (r == 1)
			I = 1 : traceMap(n, r);
		else
			I = max(1, traceMap(n, r - 1)) : traceMap(n, r);
		endif

		s1 = regexp(s(I), [fLineHeader(int2str(testbed.nodes(n,2))) ...
				"[^\n]*profile (?<snapshot>\\d+)\\s+(?<module>\\S+)\\s+(?<line>\\d+): (?<time>\\d+)" ...
				], "names");

		for k = 1 : length(s1)
			fprintf(f, "%.6f;%s;%u;%u\n", ...
				testbed.nodes(n,2) + str2double(s1(k).snapshot) / 1000000, ...
				s1(k).module, str2double(s1(k).line), str2double(s1(k).time));
		endfor

	endfor
endfor

fclose(f);
printf(" done\n\n");

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
