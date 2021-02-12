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
	error = ""	# false
	split("", override_array)	# empty array
	split("", override_array_insertion_order)	# empty array
	# Current base file section
	base_section_name = ""	# empty (global)
	# Pre-header (line immediately preceding a header)
	preheader = "" # empty

	# Parse the whole override file into an array
	parse_override_file(override_array, override_array_insertion_order)
}

function parse_override_file(array,	array_i_o,		section_name, cnt, line, commented, prepend, start, end, name, sep, raw_value, value, trimmed_line)
{
	# Current section name
	section_name = ""	# empty (global)

	cnt = 0	# numeric
	commented = ""	# false
	prepend = "" # empty

	# Read override file
	while ((getline line < (override_file)) > 0)
	{
		# Is this line a commented out normal line (;name=value)?
		if (line ~ /^[[:space:]]*[;][[:space:]]*[^[:space:];=]+[[:space:]]*[=]/)
		{
			commented = "true"
		}
		else
		{
			commented = ""	# false
		}

		# Is this line different from an ordinary comment or whitespace?
		if (! ((line ~ /^[[:space:]]*[;].*$/ && ! commented) || line ~ /^[[:space:]]*$/))
		{
			# Yes, keep processing it
			# Is this line a header?
			if (line ~ /^[[:space:]]*\[[^\];]+\][[:space:]]*(([;].*$)|$)/)
			{
				# Yes, it's a header
				# Get new section name
				start = match(line, /\[/)
				end = match(line, /\]/)
				section_name = substr(line, start+1, (end-(start+1)))
				# Subsequent lines belong to this section
				prepend = ""	# empty
			}
			else
			{
				# No, it's a normal line (possibly commented out)
				# Get field name
				start = match(line, /[^[:space:];]/)
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
				if (prepend == "")
				{
					array[section_name, name, "line"] = line
				}
				else
				{
					array[section_name, name, "line"] = prepend line
				}
				array_i_o[++cnt] = section_name SUBSEP name SUBSEP "value"
				array_i_o[++cnt] = section_name SUBSEP name SUBSEP "line"
				prepend = ""	# empty
			}
		}
		else
		{
			# No, ignore it
			if (line ~ /^[[:space:]]*$/)
			{
				prepend = "\n"
			}
			else
			{
				# Trim line trailing whitespace
				end = match(line, /[[:space:]]*$/)
				trimmed_line = substr(line, 1, (end-1))
				prepend = "\n" trimmed_line " ;ADDED\n"
			}
		}
	}
	close(override_file)
}

# Main (the empty pattern matches every input record)
{
	main_loop()
}

function main_loop(			new_header, start, end, temp)
{
	# Is this line a header?
	if ($0 ~ /^[[:space:]]*\[[^\];]+\][[:space:]]*(([;].*$)|$)/)
	{
		# Yes, it's a header
		new_header = $0
		# Flush section
		flush_section(override_array, override_array_insertion_order, base_section_name)

		# Print preheader, if available
		if (preheader)
		{
			print preheader
			preheader=""
		}
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
		# Is there a pending preheader that was not consumed?
		if (preheader)
		{
			# Process it as a normal comment
			process_base_line(preheader, base_section_name)
			preheader=""
		}
		# Is the current line a preheader?
		if ($0 ~ /^[[:space:]]*[;][[:space:]]*[Xx]{3,}[[:space:]]*$/)
		{
			# Yes, it is, so hold on processing
			preheader = $0
		}
		else
		{
			# No, resume processing
			preheader = ""	# empty
			process_base_line($0, base_section_name)
		}
	}
}

function flush_section(array, array_i_o, section_name,			i, n, sorted_idxs, j, combined, separate, printonce, temp, end, trimmed_override_line, deletions, deletions_i_o)
{
	i = 0	# numeric
	printonce = "true"
	# (Re-)Sort the insertion order array by indexes
	n = asorti(array_i_o, sorted_idxs, "@ind_num_asc")
	# Loop in the sorted array
	for (j = 1; j <= n; j++)
	{
		combined = array_i_o[sorted_idxs[j]]
		# Recover indexes
		split(combined, separate, SUBSEP)
		# Is this entry relevant?
		if (separate[1] == section_name)
		{
			if (separate[3] == "value")
			{
				# Mark entries for deletion
				deletions[++i] = section_name SUBSEP separate[2] SUBSEP "value"
				deletions_i_o[i] = sorted_idxs[j]
			}
			
			if (separate[3] == "line")
			{
				if (printonce)
				{
					printonce = ""	# false
				}
				# Trim override line trailing whitespace
				temp = array[section_name, separate[2], "line"]
				end = match(temp, /[[:space:]]*$/)
				trimmed_override_line = substr(temp, 1, (end-1))


				# Print the override
				print trimmed_override_line " ;ADDED"
				# Mark entries for deletion
				deletions[++i] = section_name SUBSEP separate[2] SUBSEP "line"
				deletions_i_o[i] = sorted_idxs[j]
			}
		}
	}
	
	# Was anything printed?
	if (printonce == "")
	{
		# Yes, so print a new line
		print ""
	}

	# Remove entries from arrays	
	i = "" # empty
	for (i in deletions)
	{
		delete array[deletions[i]];
	}
	i = "" # empty
	for (i in deletions_i_o)
	{
		delete array_i_o[deletions_i_o[i]];
	}
}

function process_base_line(base_line, section_name,			commented, start, end, base_name, override_line, trimmed_base_line, sep, raw_value, base_value, override_value, n, tmp_array, is_override_commented, i, m, deletions_i_o, trimmed_override_line)
{
	commented = ""	# false

	# Is this line whitespace?
	if (base_line ~ /^[[:space:]]*$/)
	{
		# Yes, print it through
		print base_line
		return 1	# an expression is required following the return statement
	}

	# Is this line a commented out normal line (;name=value)?
	if (base_line ~ /^[[:space:]]*[;][[:space:]]*[^[:space:];=]+[[:space:]]*[=]/)
	{
		commented = "true"
	}
	else
	{
		# Is this line an ordinary comment?
		if (base_line ~ /^[[:space:]]*[;].*$/)
		{
			# Yes, print it through
			print base_line
			return 1	# an expression is required following the return statement
		}
	}

	# Is this line a (possibly commented out) normal line (name=value)?
	if (base_line ~ /^[[:space:]]*[^[:space:];=]+[[:space:]]*[=]/ || commented)
	{
		# This is a normal line (though possibly commented out)
		# Get field name
		start = match(base_line, /[^[:space:];]/)
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

			n = split(override_line, tmp_array, "\n")
			# Is the override commented out?
			if (tmp_array[n] ~ /^[[:space:]]*[;].*$/)
			{
				is_override_commented = "true"
			}
			else
			{
				is_override_commented = ""
			}
			# Clean up arrays
			delete override_array[section_name, base_name, "value"]
			delete override_array[section_name, base_name, "line"]

			i = 0	# numeric
			for (m in override_array_insertion_order)
			{
				if (override_array_insertion_order[m] == section_name SUBSEP base_name SUBSEP "value")
				{
					deletions_i_o[++i] = m
				}
				if (override_array_insertion_order[m] == section_name SUBSEP base_name SUBSEP "line")
				{
					deletions_i_o[++i] = m
				}
			}
			i = "" # empty
			for (i in deletions_i_o)
			{
				delete override_array_insertion_order[deletions_i_o[i]];
			}

			# Is the override the same as the base?
			if (base_value == override_value)
			{
				# Yes, same value
				# Keep the base line
				if (! commented)
				{
					if (is_override_commented)
					{
						print base_line
					}
					else
					{
						print trimmed_base_line " ;FORCED"
					}
				}
				else
				{
					if (is_override_commented)
					{
						print base_line
					}
					else
					{
						# Remove ; in-place
						sub(/;/, "", trimmed_base_line)
						# Print the enabled base line
						print trimmed_base_line " ;ENABLED"
					}
				}
			}
			else
			{
				# No, different value
				if (! commented)
				{
					if (is_override_commented)
					{
						print base_line
					}
					else
					{
						# Comment the base line
						print ";" trimmed_base_line " ;OVERRIDDEN"
						# Trim override line leading NL, if present
						start = match(override_line, /[^\n]/)
						trimmed_override_line = substr(override_line, start)
						# Print the override
						print trimmed_override_line
					}
				}
				else
				{
					if (is_override_commented)
					{
						# Keep commented out base line
						print base_line
						# Trim override line trailing whitespace and leading NL, if present
						start = match(override_line, /[^\n]/)
						end = match(override_line, /[[:space:]]*$/)
						trimmed_override_line = substr(override_line, start, (end-start))
						# Print the override
						print trimmed_override_line " ;ADDED"
					}
					else
					{
						# Keep commented out base line
						print base_line
						# Trim override line trailing whitespace and leading NL, if present
						start = match(override_line, /[^\n]/)
						end = match(override_line, /[[:space:]]*$/)
						trimmed_override_line = substr(override_line, start, (end-start))
						# Print the override
						print trimmed_override_line " ;ADDED"
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
	else
	{
		# Invalid line
		print "ERROR: Invalid line " NR ". Aborting."
		error = "true"
		exit 1
	}
}

END {
	# Was there an error?
	if (error)
	{
		# Yes, exit immediately
		exit 1
	}
	else
	{
		# No, all is fine
		# Flush new sections
		flush_array()
	}
}

function flush_array(			section_name, n, sorted_idxs, i, separate)
{
	# Flush last section
	flush_section(override_array, override_array_insertion_order, base_section_name)
	# Is there a pending preheader that was not consumed?
	if (preheader)
	{
		# Process it as a normal comment
		process_base_line(preheader, base_section_name)
		print ""
		preheader=""
	}

	section_name = ""	# empty (global)
	# (Re-)Sort the insertion order array by indexes
	n = asorti(override_array_insertion_order, sorted_idxs, "@ind_num_asc")
	# Loop in the sorted array
	for (i = 1; i <= n; i++)
	{
		# Recover indexes
		split(override_array_insertion_order[sorted_idxs[i]], separate, SUBSEP)
		# Is it a new section?
		if (separate[1] != section_name)
		{
			# Yes, new section
			section_name = separate[1]
			# Print it
			print ";XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"
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
