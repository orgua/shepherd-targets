%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

1;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function x = read_field(raw_data, type_)

	switch (type_)
		case 0x82
			d = uint16(raw_data);
			x = d(1) * 0x100 + d(2) * 0x1;
		case 0x83
			d = uint16(raw_data);
			x = d(1) * 0x1 + d(2) * 0x100;
		case 0x84
			d = uint32(raw_data);
			x = d(1) * 0x1000000 + d(2) * 0x10000 + d(3) * 0x100 + d(4) * 0x1;
		case 0x85
			d = uint32(raw_data);
			x = d(1) * 0x1 + d(2) * 0x100 + d(3) * 0x10000 + d(4) * 0x1000000;
		otherwise
			error("internal");
	endswitch

endfunction

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

[fileName, path] = uigetfile({'*.csv'}, 'Load profile data (cancel to reuse loaded data)');
if (fileName)

	dataFile = [path fileName];

	[fileName, path] = uigetfile({'*.bin'}, 'Load profile info', path);
	if (!fileName)
		return;
	endif
	infoFile = [path fileName];

	% read data

	f = fopen(dataFile, "rb");

	fseek(f, 0, SEEK_END);
	len = ftell(f);
	fseek(f, 0, SEEK_SET);
	if (len > 100 * 1024^2)
		b = questdlg( ...
				[sprintf("File size is quite large (%d MB),\n", round(len / 1024^2)) ...
				"processing may be slow and memory consuming.\nContinue?"], ...
				"Warning", "Cancel", "Ok", "Cancel");
		if (!strcmp(b, "Ok"))
			return;
		endif
	endif

	s = fread(f, [1, inf], "*char");
	fclose(f);

	%%%%%%%%%%%%%%%%%
	% import data

	checkpoints = cell(0);
	snapshots = [];
	profile = repmat(double(nan), [0, 0]);

	printf("importing profile data ...\n"); fflush(stdout);

	s1 = regexp(s, ["(?<snapshot>[^;]+);(?<module>\\S+);(?<line>\\d+);(?<time>\\d+)"], "names");
	for k = 1 : length(s1)

		snapshot = str2double(s1(k).snapshot);
		s = lookup(snapshots, snapshot, "m");
		if (!s)
			snapshots = union(snapshots, snapshot);
			s = lookup(snapshots, snapshot, "m");
			profile(:, end + 1 : s) = nan;
		endif

		t = [s1(k).module " " sprintf("%5d", str2double(s1(k).line))];
		c = find(strcmp(checkpoints, t), 1);
		if (isempty(c))
			checkpoints{end + 1} = t;
			c = length(checkpoints);
			profile(end + 1 : c, :) = nan;
		endif

		profile(c, s) = str2double(s1(k).time);

	endfor

	% free space
	s1 = [];

	% postprocess data

%	printf("postprocessing profile data ...\n"); fflush(stdout);

	% identical timestamps in consecutive snapshots are interpreted as no-exec
	for s = size(profile, 2) : -1 : 2
		d = find(profile(:, s) == profile(:, s - 1));
		profile(d, s) = nan;
	endfor

	% sort
	% ATTENTION: At this point all checkpoints have internally generated names.
	% This ensures that checkpoints that belong to the same function appear in
	% consecutive order, and the first/last checkpoint inside a function can be
	% interpreted as function entry/return.
	[checkpoints, I] = sort(checkpoints);
	profile = profile(I,:);

	cp = struct();
	cp(length(checkpoints)).name = "";
	[cp.name] = deal(checkpoints{:});
	[cp.priority] = deal(nan);

	%%%%%%%%%%%%%%%%%
	% import info

	printf("importing profile info ...\n"); fflush(stdout);

	f = fopen(infoFile, "rb");
	s = fread(f, [1, inf], "*uint8");
	fclose(f);

	% records: <position> <marker (incl. byteorder)> <size> <type>
	records = repmat(uint16(0), 0, 4);

	% scan records
	k = 1;
	while (k <= length(s))

		if ((s(k) != 0x80) && (s(k) != 0x81))
			k += 1;
			continue;
		endif

		records(end + 1, 1:2) = [k, s(k)];

		if (k + 1 > length(s))
			error("info record at offset %u: invalid format", k);
		endif
		if (s(k) == 0x80)
			len = uint16(s(k + 1)) * 0x100 + uint16(s(k + 2));
		else
			len = uint16(s(k + 1)) + uint16(s(k + 2)) * 0x100;
		endif
		records(end, 3) = len;
		if (k + len > length(s) + 1)
			error("info record at offset %u: invalid size", k);
		endif

		records(end, 4) = s(k + 3);

		k += len;

	endwhile

	read16 = @(r,k) read_field(s(records(r,1) + k : records(r,1) + k + 1), records(r,2) + 2);
	read32 = @(r,k) read_field(s(records(r,1) + k : records(r,1) + k + 3), records(r,2) + 4);

	% get timestamp config
	r = find(records(:,4) == 2, 1);
	if (r && records(r,3) >= 12)
		timestamp_frequency = double(read32(r,4));
		timestamp_range = double(read32(r,8)) + 1;
	endif

	% import checkpoint infos
	for r = find(records(:,4) == 4)(:)'

		if (records(r,2) < 14)
			error("info record at offset %u: invalid format (size)", records(r,1));
		endif

		link = int32(read16(r,4));
		if (link >= 0x8000)
			link -= 0x10000;
		endif
		link += int32(records(r,1));

		k = lookup(records(:,1), link, "m");
		if (!k)
			error("info record at offset %u: invalid link", records(r,1));
		endif
		if (records(k,4) != 3)
			error("info record at offset %u: link to invalid type", records(r,1));
		endif

		module = strtrim(strrep(char(s(records(k,1) + 4 : records(k,1) + records(k,3) - 1)), "\0", " "));
		line = read16(r,6);
		t = [module " " sprintf("%5d", line)];
		k = find(strcmp(checkpoints, t), 1);

		if (k)

			cp(k).func_id = read32(r,8);
			cp(k).priority = s(records(r,1) + 12);

			name = strtrim(strrep(char(s(records(r,1) + 13 : records(r,1) + records(r,3) - 1)), "\0", " "));
			if (!isempty(name))
				checkpoints{k} = name;
%				checkpoints{k} = sprintf("%-50s   (%s)", name, checkpoints{k});
				cp(k).name = checkpoints{k};
			endif

		endif

	endfor

	printf("import done\n");

endif

%%%%%%%%%%%%%%%%%%%%%%%
% config measurement

global params;
params = struct();
params.ok = 0;
params.from = 1;
params.to = 1;
params.overhead = 20;
params.figcmd = 'figure(); set(gcf(), "name", "TODO");';

hDialog = dialog("position", [1, 1, 1000, 710]);

uicontrol(hDialog, "style", "pushbutton", "position", [400, 10, 200, 30], ...
	"string", "Ok", ...
	"callback", 'global params; params.ok = 1; delete(gcbf());');

uicontrol(hDialog, "style", "edit", "position", [10, 65, 980, 25], ...
	"string", params.figcmd, "horizontalalignment", "left", ...
	"deletefcn", 'global params; params.figcmd = get(gcbo(), "string");');

uicontrol(hDialog, "style", "text", "position", [12, 90, 980, 25], ...
	"string", "figure commands", "horizontalalignment", "left");

uicontrol(hDialog, "style", "edit", "position", [10, 120, 980, 25], ...
	"string", int2str(params.overhead), "horizontalalignment", "left", ...
	"deletefcn", 'global params; params.overhead = str2double(get(gcbo(), "string"));');

uicontrol(hDialog, "style", "text", "position", [12, 145, 980, 25], ...
	"string", "static (or mean) preemption overhead [ticks]", "horizontalalignment", "left");

uicontrol(hDialog, "style", "listbox", "position", [10, 180, 490, 500], ...
	"string", checkpoints, "value", params.from, "fontname", "Courier New", ...
	"callback", 'global params; params.from = get(gcbo(), "value");');

uicontrol(hDialog, "style", "text", "position", [12, 680, 480, 25], ...
	"string", "measure from", "horizontalalignment", "left");

uicontrol(hDialog, "style", "listbox", "position", [500, 180, 490, 500], ...
	"string", checkpoints, "value", params.to, "fontname", "Courier New", ...
	"callback", 'global params; params.to = get(gcbo(), "value");');

uicontrol(hDialog, "style", "text", "position", [502, 680, 480, 25], ...
	"string", "to", "horizontalalignment", "left");

waitfor(hDialog);

if (!params.ok)
	return;
endif

%%%%%%%%%%%%%%%%%%%%%%%
% compute data

data = mod(profile(params.to, :) - profile(params.from, :), timestamp_range);

% strip execution time of higher priority threads (e.g. ISRs)
I1 = find([cp.priority] < min(cp(params.from).priority, cp(params.to).priority));
if (!isempty(I1))

	% delimit functions
	I = zeros(0, 2);
	while (!isempty(I1))
		I2 = find([cp.func_id] == cp(I1(1)).func_id);
		if (!isempty(find([cp(I2).priority] != cp(I2(1)).priority)))
			error("inconsistent priorities within same function (%s)", cp(I2(1)).name);
		endif
		I(end + 1, :) = [I2(1), I2(end)];
		I1 = setdiff(I1, I2);
	endwhile

	% sort by priority
	[~, I1] = sort([cp(I(:,1)).priority]);
	I = I(I1,:);

	% ask user
	s = strcat({cp(I(:,1)).name}, {" ... "}, {cp(I(:,2)).name});
	[s, ok] = listdlg("ListString", s, "InitialValue", [1:length(s)], ...
		"ListSize", [600, 500], "Name", "higher priority threads", "PromptString", {
		"Select all higher priority activities (threads, ISRs)",
		"whose execution times should be stripped from the measurement"});
	if (!ok)
		return;
	endif
	I = I(s,:);

	% strip nested execution times
	I(end + 1, :) = [params.from, params.to];
	for s = 1 : length(snapshots)
		I(:,3) = 0;
		for k = 1 : rows(I)
			for m = k + 1 : rows(I)
				if (mod(profile(I(k,1), s) - profile(I(m,1), s), timestamp_range) < ...
					mod(profile(I(m,2), s) - profile(I(m,1), s), timestamp_range))
					I(m,3) += ...
						mod(profile(I(k,2), s) - profile(I(k,1), s), timestamp_range) + ...
						params.overhead - I(k,3);
				endif
			endfor
		endfor
		data(s) -= I(end,3);
	endfor

endif

% scale to microseconds
data = data ./ (timestamp_frequency / 1e6);

% plot
eval([params.figcmd ";"]);
subplot(2,1,1);
plot(snapshots, data, "o");
ylim(min(ylim(), [0, inf]));
grid on;
xlabel("snapshot");
ylabel("execution time [us]");
subplot(2,1,2);
min_ = min(min(data)); max_ = max(max(data));
bins = min_ : max(10 / timestamp_frequency, (max_ - min_) / 50) : max_;
if (length(bins) < 2)
	bins = 5;
endif
hist(data, bins);
grid on;
xlabel("execution time [us]");
ylabel("frequency [#snapshots]");

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
