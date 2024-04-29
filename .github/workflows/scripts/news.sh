#!/bin/bash

repo="$1"
news="$2"

function Usage()
{
    error=$1

    echo ""
    echo "USAGE:  $(basename $0) [github-repository] [news-file] [keyword...]"
    echo ""

    if [ -n "$error" ]; then
       echo "ERROR: $error"
       echo ""
    fi

    exit 1
}

for word in ${@:3}; do
    keywords="$keywords|$word"
done
keywords="${keywords#|}"

[ -z "$repo" ]     && Usage "Missing repository"
[ -z "$news" ]     && Usage "Missing news file"
[ -z "$keywords" ] && Usage "Missing keyword(s)"

#echo "Repository: $repo"
#echo "Output:     $news"
#echo "Keywords:   $keywords"
#echo ""

# get last release, excluding drafts/prereleases, and extract tag/url
release=$(curl -sL https://api.github.com/repos/$repo/releases | jq -r '[.[] | select(.draft == false and .prerelease == false)][0]') #'
tag="$(echo "$release" | jq -r '.tag_name')"
url="$(echo "$release" | jq -r '.html_url')"

header="otable changes since last release ([$tag]($url))"

git log --no-merges ${tag}..HEAD --format="%B" > "$news"

# cleanup all lines
sed -ri 's/^[\ \-]+//' "$news"

# remove all lines not starting with keywords
sed -ri "/^(${keywords}):/!d" "$news"

# remove unwanted entries
if [[ "$repo" == "rotators/Fo1in2" ]] && [[ "$tag" == "v1.9.3324" ]]; then
   sed -ri "/^Added: New mini-mod that replaced the rerecorded narrator lines for the expanded ending slides/d" "$news"
fi

# create a list, make keywords bold
sed -ri 's!^([A-Za-z]+)!- **\1**!' "$news"

sort "$news" > "$news.stupid-sort"
mv -f "$news.stupid-sort" "$news"

# add header
if [ -s "$news" ]; then
   sed -i "1s!^!N${header}\\n\\n!" "$news"
else
   echo "No n$header" > "$news"
fi

unix2dos -q "$news"
