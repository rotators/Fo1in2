#!/bin/bash

set -e

repo="$1"
news="$2"

function Usage()
{
    echo ""
    echo "USAGE:  $(basename $0) [github-repository] [news-file] [keyword...]"
    echo ""

    exit 1
}

for word in ${@:3}; do
    keywords="$keywords|$word"
done
keywords="${keywords#|}"

if   [ -z "$repo" ]; then
     echo "Missing repository"
     Usage
elif [ -z "$news" ]; then
     echo "Missing news file"
     Usage
elif [ -z "$keywords" ]; then
     echo "Missing keywords"
     Usage
fi

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

# create a list, make keywords bold
sed -ri 's!^([A-Za-z]+)!- **\1**!' "$news"

sort -o "$news" "$news"

# add header
if [ -s "$news" ]; then
   sed -i "1s!^!N${header}\\n!" "$news"
else
   echo "No n$header" > "$news"
fi

unix2dos -q "$news"
