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

# awk -v override_file=override.ini -f mergeini.awk base.ini

BEGIN {
	# The override file name must be passed in the command line arguments with -v
	if (! override_file) {
		print ""
		print "mergeini.awk: print into stdout the merge of an override and base .ini files"
		print "Copyright (C) 2021 jalt"
		print "Usage: awk -v override_file=<override.ini> -f mergeini.awk <base.ini>"
		print ""
		exit 1
	}

	# Global variables
	split("", override_array)	# empty array
	# Current base file section
	base_section_name = ""	# empty (global)

	# Parse the whole override file into an array
	parse_override_file(override_array)
}

function parse_override_file(array,			section_name, line, start, end, name, sep, raw_value, value)
{
	# Current section name
	section_name = ""	# empty (global)

	# Read override file
	while ((getline line < (override_file)) > 0)
	{
		# Is this line different from a comment or whitespace?
		if (! (line ~ /^[[:space:]]*[;].*$/ || line ~ /^[[:space:]]*$/))
		{
			# Yes, keep processing it
			# Is this line a header?
			if (line ~ /^[[:space:]]*\[.+\][[:space:]]*(([;].*$)|$)/)
			{
				# Yes, it's a header
				# Get new section name
				start = match(line, /\[/)
				end = match(line, /\]/)
				section_name = substr(line, start+1, (end-(start+1)))
				# Subsequent lines belong to this section
			}
			else
			{
				# No, it's a normal line
				# Get field name
				start = match(line, /^[^[:space:]]/)
				end = match(line, /[[:space:]]*=/)
				name = substr(line, start, (end-start))
				# Get field value
				sep = match(line, /=/)
				raw_value = substr(line, sep+1)
				start = match(raw_value, /^[^[:space:]]/)
				end = match(raw_value, /[[:space:]]*(([;].*$)|$)/)
				value = substr(raw_value, start, (end-start))
				# Store everything in the array
				# "" is a valid array index in awk (global)
				array[section_name, name, "value"] = value
				array[section_name, name, "line"] = line
			}
		}
	}
	close(override_file)
}

# Main (the empty pattern matches every input record)
{
	main_loop()
}

function main_loop(			new_header, start, end)
{
	# Is this line a header?
	if ($0 ~ /^[[:space:]]*\[.+\][[:space:]]*(([;].*$)|$)/)
	{
		# Yes, it's a header
		new_header = $0
		# Flush section
		flush_section(override_array, base_section_name)
		# Print new header
		print new_header
		# Get new section name
		start = match(new_header, /\[/)
		end = match(new_header, /\]/)
		base_section_name = substr(new_header, start+1, (end-(start+1)))
		# Subsequent lines belong to this section
	}
	else
	{
		# No, it's a normal line, comment or whitespace
		process_base_line($0, base_section_name)
	}
}

function flush_section(array, section_name,			i, combined, separate, temp, end, trimmed_override_line, deletions)
{
	i = 0	# numeric
	# Loop in the array
	for (combined in array) {
		# Recover indexes
		split(combined, separate, SUBSEP)
		# Is this entry relevant?
		if (separate[1] == section_name && separate[3] == "line")
		{
			# Trim override line trailing whitespace
			temp = array[section_name, separate[2], "line"]
			end = match(temp, /[[:space:]]*$/)
			trimmed_override_line = substr(temp, 1, (end-1))
			# Print the override
			print trimmed_override_line " ;ADDED"
			# Mark entries for deletion
			deletions[++i] = section_name SUBSEP separate[2] SUBSEP "line"
			deletions[++i] = section_name SUBSEP separate[2] SUBSEP "value"
		}
	}
	
	i = "" # empty
	# Remove entries from array
	for (i in deletions)
	{
		delete array[deletions[i]];
	}
}

function process_base_line(base_line, section_name,			start, end, base_name, override_line, trimmed_base_line, sep, raw_value, base_value, override_value)
{
	# Is this line a comment or whitespace?
	if (base_line ~ /^[[:space:]]*[;].*$/ || base_line ~ /^[[:space:]]*$/)
	{
		# Yes, print it through
		print base_line
	}
	else
	{
		# No, it's a normal line
		# Get field name
		start = match(base_line, /^[^[:space:]]/)
		end = match(base_line, /[[:space:]]*=/)
		base_name = substr(base_line, start, (end-start))
		# Find override
		if ((section_name, base_name, "value") in override_array)
		{
			# There is an override
			# Trim base line trailing whitespace
			end = match(base_line, /[[:space:]]*$/)
			trimmed_base_line = substr(base_line, 1, (end-1))

			# Get base value
			sep = match(base_line, /=/)
			raw_value = substr(base_line, sep+1)
			start = match(raw_value, /^[^[:space:]]/)
			end = match(raw_value, /[[:space:]]*(([;].*$)|$)/)
			base_value = substr(raw_value, start, (end-start))

			# Get override
			override_value = override_array[section_name, base_name, "value"]
			override_line = override_array[section_name, base_name, "line"]
			delete override_array[section_name, base_name, "value"]
			delete override_array[section_name, base_name, "line"]

			# Is the override the same as the base?
			if (base_value == override_value)
			{
				# Yes, same value
				# Keep the base line
				print trimmed_base_line " ;FORCED"
			}
			else
			{
				# No, different value
				# Comment the base line
				print ";" trimmed_base_line " ;OVERRIDEN"
				# Print the override
				print override_line
			}
		}
		else
		{
			# There is no override, keep the base line
			print base_line
		}
	}
}

END {
	# Flush new sections
	flush_array()
}

function flush_array(			section_name, n, sorted_idxs, i, separate)
{
	section_name = ""	# empty (global)
	# Sort the array by indexes
	n = asorti(override_array, sorted_idxs, "@ind_str_asc")

	# Loop in the sorted array
	for (i = 1; i <= n; i++)
	{
		# Recover indexes
		split(sorted_idxs[i], separate, SUBSEP)
		# Is it a new section?
		if (separate[1] != section_name)
		{
			# Yes, new section
			section_name = separate[1]
			# Print it
			print "[" section_name "] ; ADDED"
		}
		# Is it a line?
		if (separate[3] == "line")
		{
			# Yes it is
			print override_array[section_name, separate[2], "line"]
		}
	}
}
