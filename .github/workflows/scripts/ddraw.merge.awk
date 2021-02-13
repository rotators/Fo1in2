# mergeini.awk: print into stdout the merge of an override and base .ini files

# MIT License
#
# Copyright (c) 2021 jalt
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# awk -v override_file=override.ini -v adornments=inline -f mergeini.awk base.ini

BEGIN {
	# The override file name must be passed in the command line arguments with -v
	if (! override_file)
	{
		print ""
		print "mergeini.awk: print into stdout the merge of an override and base .ini files"
		print "Copyright (C) 2021 jalt"
		print "Usage: awk -v override_file=<override.ini> [-v adornments=<none|inline|around>] -f mergeini.awk <base.ini>"
		print ""
		exit 1
	}
	if (adornments != "inline" && adornments != "around")
	{
		adornments = ""
	}

	# Global variables
	error = ""	# false
	split("", override_array)	# empty array
	split("", override_array_insertion_order)	# empty array
	base_section_name = ""	# empty (global)
	preheader = "" # empty

	parse_override_file(override_array, override_array_insertion_order)
}

# Read and parse the whole override file into an array
function parse_override_file(array,	array_i_o,		section_name, prepend, j, line, class, res)
{
	section_name = ""	# empty (global)
	prepend = ""	# empty
	j = 0	# numeric

	# Read override file
	while ((getline line < (override_file)) > 0)
	{
		class = classify(line);
		if (class == "header")
		{
			# New section name (subsequent lines belong to this section)
			parse(line, res, class)
			section_name = res["section"]
			# Clear pending lines
			prepend = ""	# empty
			continue
		}

		if (class == "disabled" || class == "normal")
		{
			# Store everything in the array
			# "" is a valid array index in awk (global)
			parse(line, res, class)
			array[section_name, res["key"], "value"] = res["value"]
			array[section_name, res["key"], "line"] = prepend line
			array_i_o[++j] = section_name SUBSEP res["key"] SUBSEP "value"
			array_i_o[++j] = section_name SUBSEP res["key"] SUBSEP "line"
			# Clear pending lines
			prepend = ""	# empty
			continue
		}

		if (class == "whitespace")
		{
			# Tentatively prepend an empty line to the next line
			prepend = "\n"
			continue
		}

		if (class == "comment" || class == "preheader")
		{
			# Tentatively prepend this to the next line
			if (adornments == "inline")
				prepend = prepend trim_trailing_whitespace(line) " ;ADDED\n"
			else
				prepend = prepend line
			continue
		}
	}
	close(override_file)
}

# Main (the empty pattern matches every input record)
{
	main_loop()
}

# Do for every line in the base file
function main_loop(			class, new_header, res)
{
	class = classify($0);
	if (class == "header")
	{
		# New section name (subsequent lines belong to this section)
		new_header = $0
		# Flush current section
		flush_section(override_array, override_array_insertion_order, base_section_name)
		# Print preheader, if available
		if (preheader != "")
		{
			print preheader
			preheader = ""
		}
		# Print new header
		print new_header
		# Get new section name
		parse(new_header, res, class)
		base_section_name = res["section"]
	}
	else
	{
		# Is there a pending preheader that was not consumed?
		if (preheader != "")
		{
			# Consider it a normal comment
			print preheader
			preheader = ""
		}

		if (class == "preheader")
		{
			# Hold on processing
			preheader = $0
		}
		else
		{
			# Resume processing
			preheader = ""	# empty
			if (class == "comment" || class == "whitespace")
				print $0
			else
			{
				if (class == "normal" || class == "disabled")
					process_base_line($0, base_section_name, class)
				else
				{
					# Invalid line found, proceed to END after signaling the fatal error
					print "ERROR: Invalid line " NR " in file " FILENAME ". Aborting."
					error = "true"
					exit 1
				}
			}
		}
	}
}

# Flush remaining lines in the array that belong to this section
function flush_section(array, array_i_o, section_name,			j, n, sorted_idxs, i, separate, override_line, deletions, deletions_i_o)
{
	j = 0	# numeric
	# Re-sort the insertion order array by indexes
	n = asorti(array_i_o, sorted_idxs, "@ind_num_asc")
	# Loop in the sorted array
	for (i = 1; i <= n; i++)
	{
		# Recover indexes
		split(array_i_o[sorted_idxs[i]], separate, SUBSEP)
		if (separate[1] == section_name)
		{
			# This entry is in the desired section
			if (adornments == "around")
			{
				if (j == 0)
					print ";v>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>v"
			}

			if (separate[3] == "line")
			{
				# Print the override
				override_line = array[section_name, separate[2], "line"]
				if (adornments == "inline")
					print trim_trailing_whitespace(override_line) " ;ADDED"
				else
				{
					print override_line
				}
			}
			# Mark entry for deletion
			++j
			deletions[j] = section_name SUBSEP separate[2] SUBSEP separate[3]
			deletions_i_o[j] = sorted_idxs[i]
		}
	}

	# If anything was printed, print an empty line
	if (j > 0) {
		if (adornments == "around")
			print ";^>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>^"
		print ""
	}

	# Remove entries from arrays
	for (i in deletions)
		delete array[deletions[i]];
	for (i in deletions_i_o)
		delete array_i_o[deletions_i_o[i]];
}

function process_base_line(base_line, section_name, base_class,			base_res, override_value, override_line, j, k, deletions_i_o, override_line_count, tmp_array, trimmed_base_line, trimmed_override_line)
{
	parse(base_line, base_res, base_class)
	# Find override
	if ((section_name, base_res["key"], "value") in override_array)
	{
		override_value = override_array[section_name, base_res["key"], "value"]
		override_line = override_array[section_name, base_res["key"], "line"]
		# Clean up arrays
		delete override_array[section_name, base_res["key"], "value"]
		delete override_array[section_name, base_res["key"], "line"]
		j = 0	# numeric
		for (k in override_array_insertion_order)
		{
			if ((override_array_insertion_order[k] == section_name SUBSEP base_res["key"] SUBSEP "value") || (override_array_insertion_order[k] == section_name SUBSEP base_res["key"] SUBSEP "line"))
			{
				deletions_i_o[++j] = k
			}
		}
		for (j in deletions_i_o)
			delete override_array_insertion_order[deletions_i_o[j]];

		# The override may have prepended comments or an empty line
		override_line_count = split(override_line, tmp_array, "\n")
		# Classify the override
		override_class = classify(tmp_array[override_line_count]);

		# Trim trailing whitespace
		trimmed_base_line = trim_trailing_whitespace(base_line)
		trimmed_override_line = trim_leading_newline(override_line)

		# Is the override the same as the base?
		if (base_res["value"] == override_value)
		{
			if (override_class == "disabled")
				print base_line
			else
			{
				if (base_class == "normal")
				{
					if (adornments == "inline")
						print trimmed_base_line " ;FORCED"
					else
					{
						if (adornments == "around")
						{
							print ";v================================================v"
							print base_line
							print ";^================================================^"
						}
						else
							print base_line
					}
				}
				else
				{
					if (adornments == "inline")
					{
						# Remove ; in-place
						sub(/;/, "", trimmed_base_line)
						print trimmed_base_line " ;ENABLED"
					}
					else
					{
						if (adornments == "around")
						{
							print ";vEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEv"
							sub(/;/, "", base_line)
							print base_line
							print ";^EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE^"
						}
						else
						{
							# Remove ; in-place
							sub(/;/, "", base_line)
							print base_line
						}
					}
				}
			}
		}
		else
		{
			if (base_class == "normal")
			{
				if (override_class == "disabled")
					print base_line
				else
				{
					if (adornments == "inline")
					{
						# Comment the base line
						print ";" trimmed_base_line " ;OVERRIDDEN"
						# Print the override
						print trimmed_override_line
					}
					else
					{
						if (adornments == "around")
						{
							print ";v<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<v"
							# Comment the base line
							print ";" base_line
							print trimmed_override_line
							print ";^>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>^"
						}
						else
						{
							# Comment the base line
							print ";" base_line
							# Print the override
							print trimmed_override_line
						}
					}
				}
			}
			else
			{
				if (adornments == "inline")
				{
					# Keep commented out base line
					print base_line
					# Print the override
					print trim_trailing_whitespace(trimmed_override_line) " ;ADDED"
				}
				else
				{
					if (adornments == "around")
					{
						print ";v================================================v"
						# Keep commented out base line
						print base_line
						# Print the override
						print trimmed_override_line
						print ";^>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>^"
					}
					else
					{
						# Keep commented out base line
						print base_line
						# Print the override
						print trimmed_override_line
					}
				}
			}
		}
	}
	else
	{
		# There is no override, keep the base line
		print base_line
	}
}

END {
	# Flush any remaining array entries, unless there was an error
	if (error)
		exit 1
	else
		flush_array()
}

# Flush remaining lines in the array
function flush_array(			section_name, n, sorted_idxs, i, ran_once, separate)
{
	# Flush current (last) section
	flush_section(override_array, override_array_insertion_order, base_section_name)

	# Is there a pending preheader that was not consumed?
	if (preheader != "")
	{
		# Process it as an ordinary comment
		print preheader
		preheader = ""
		# Print an empty line
		print ""
	}

	ran_once = ""	# false
	section_name = ""	# empty (global)
	# Re-sort the insertion order array by indexes
	n = asorti(override_array_insertion_order, sorted_idxs, "@ind_num_asc")
	# Loop in the sorted array
	for (i = 1; i <= n; i++)
	{
		# Recover indexes
		split(override_array_insertion_order[sorted_idxs[i]], separate, SUBSEP)
		if (separate[1] != section_name)
		{
			if (adornments == "around" && ! ran_once)
			{
				print ";v>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>v"
				ran_once = "true"
			}
			# New section name (subsequent lines belong to this section)
			section_name = separate[1]
			print ";XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
			if (adornments == "inline")
				print "[" section_name "] ; ADDED"
			else
				print "[" section_name "]"
		}
		if (separate[3] == "line")
		{
			# Print override
			print override_array[section_name, separate[2], "line"]
		}
	}
	if (adornments == "around" && ran_once)
	{
		print ";^>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>^"
	}
}

# Classify a line
function classify(line)
{
	if (line ~ /^[[:space:]]*$/)
		return "whitespace"	

	if (line ~ /^[[:space:]]*[;][[:space:]]*[^[:space:];=]+[[:space:]]*[=]/)
		return "disabled"

	if (line ~ /^[[:space:]]*[;][[:space:]]*[Xx]{3,}[[:space:]]*$/)
		return "preheader"

	if (line ~ /^[[:space:]]*[;].*$/)
		return "comment"

	if (line ~ /^[[:space:]]*\[[^\];]+\][[:space:]]*(([;].*$)|$)/)
		return "header"

	if (line ~ /^[[:space:]]*[^[:space:];=]+[[:space:]]*[=]/)
		return "normal"

	return "invalid"
}

# Parse a "normal", "disabled", or "header" line into a result array
function parse(line, result, opt_classification,			start, end, sep, raw_value)
{
	# Clear result array
	split("", result)	# empty array

	# If unclassified, classify
	if (opt_classification == "")
		opt_classification = classify(line)

	if (opt_classification == "header")
	{
		# Get section name
		start = match(line, /\[/)
		end = match(line, /\]/)
		result["section"] = substr(line, start+1, (end-(start+1)))
	}
	else
	{
		if (opt_classification == "normal" || opt_classification == "disabled")
		{
			# Get key
			start = match(line, /[^[:space:];]/)
			end = match(line, /[[:space:]]*=/)
			result["key"] = substr(line, start, (end-start))
			# Get value
			sep = match(line, /=/)
			raw_value = substr(line, sep+1)
			start = match(raw_value, /[^[:space:]]/)
			end = match(raw_value, /[[:space:]]*(([;].*$)|$)/)
			result["value"] = substr(raw_value, start, (end-start))
		}
	}
}

# Trim trailing whitespace
function trim_trailing_whitespace(line,			end)
{
	end = match(line, /[[:space:]]*$/)
	return substr(line, 1, (end-1))
}

# Trim leading newline
function trim_leading_newline(line,			start)
{
	start = match(line, /[^\n]/)
	return substr(line, start)
}
