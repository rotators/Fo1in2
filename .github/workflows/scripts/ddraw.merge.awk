BEGIN {
	isinsection = ""
	header = ""
	newheader = ""
}

function findoverrideinglobal(origlineg)
{
	o_regexpg="^[[:space:]]*" origlineg "[[:space:]]*="
	retg=""
	while ((getline overlineg < (overridefile)) > 0)
	{
		# Is this line a header?
		if (overlineg ~ /^[[:space:]]*\[.+\][[:space:]]*$/)
		{
			# Not found
			break
		}
		
		# Is this line a match?
		if (overlineg ~ o_regexpg)
		{
			# Found!
			retg=overlineg
			break
		}
	}
	close(overridefile)
	return retg
}

function findoverrideinsection(origline, origsection)
{
	o_regexp="^[[:space:]]*" origline "[[:space:]]*="
	o_regexph="^[[:space:]]*\\[" origsection "\\][[:space:]]*$"
	ret=""
	foundh=""
	while ((getline overline < (overridefile)) > 0)
	{
		if (! foundh)
		{
			# Is this line the right header?
			if (overline ~ o_regexph)
			{
				# Header found
				foundh="true"
			}
		}
		else
		{
			# Is this line a header?
			if (overline ~ /^[[:space:]]*\[.+\][[:space:]]*$/)
			{
				# Not found
				break
			}
		
			# Is this line a match?
			if (overline ~ o_regexp)
			{
				# Found!
				ret=overline
				break
			}
		}
	}
	close(overridefile)
	return ret
}


function inglobal(oglineg)
{
	# Is this line a comment or whitespace?
	if (oglineg ~ /^[[:space:]]*[;].*$/ || oglineg ~ /^[[:space:]]*$/)
	{
		# Yes, print it through
		print oglineg
	}
	else
	{
		# No, it's a normal line
		# Trim initial whitespace
		begg = match(oglineg, /^[^[:space:]]/)
		tempg = substr(oglineg, begg)
		# Get field name
		split(tempg, farrayg, "=")
		fnameg = farrayg[1]
		overg=findoverrideinglobal(fnameg)
		if (overg == "")
		{
			# There is no override, keep the original
			print oglineg
		}
		else
		{
			# Print the override
			print "vvv OVERRIDEN by Fo1in2 vvv"
			print ";" oglineg
			print overg
			print "^^^ OVERRIDEN by Fo1in2 ^^^"
		}
	}
}

function insection(ogline, ogsection)
{
	# Is this line a comment or whitespace?
	if (ogline ~ /^[[:space:]]*[;].*$/ || ogline ~ /^[[:space:]]*$/)
	{
		# Yes, print it through
		print ogline
	}
	else
	{
		# No, it's a normal line
		# Trim initial whitespace
		beg = match(ogline, /^[^[:space:]]/)
		temp = substr(ogline, beg)
		# Get field name
		split(temp, farray, "=")
		fname = farray[1]
		over=findoverrideinsection(fname, ogsection)
		if (over == "")
		{
			# There is no override, keep the original
			print ogline
		}
		else
		{
			# Print the override
			print "vvv OVERRIDEN by Fo1in2 vvv"
			print ";" ogline
			print over
			print "^^^ OVERRIDEN by Fo1in2 ^^^"
		}
	}
}

{
	# Is this line in any section?
	if (! isinsection)
	{
		# No, it's global
		# Is this line a header?
		if ($0 ~ /^[[:space:]]*\[.+\][[:space:]]*$/)
		{
			# Yes, it's a header
			newheader = $0
			# Flush global section
			#flushglobal()
			header = newheader
			# Print header
			print header
			# Next lines belong to this section
			isinsection = "true"
		}
		else
		{
			# No, it's a normal global line
			inglobal($0)
		}
	}
	else
	{
		# Yes, it's inside section $header
		# Is this line a new header?
		if ($0 ~ /^[[:space:]]*\[.+\][[:space:]]*$/)
		{
			# Yes, it's a header
			newheader = $0
			# Flush section
			#flushsection($header)
			header = newheader
			# Print header
			print header
			# Next lines belong to this section
			isinsection = "true"
		}
		else
		{
			# No, it's a normal line
			# Trim initial whitespace
			begm = match(header, /\[/)
			endm = match(header, /\]/)
			tempm = substr(header, begm+1, (endm-(begm+1)))
			insection($0, tempm)
		}
	}
}
