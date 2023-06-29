- Add great features and amazing improvements

- Update `MOD_VERSION` in [version.sh](../.github/workflows/scripts/version.sh)

- Upload release header to [Resources/Gallery/releases/](../../../tree/master/Resources/Gallery/releases) (_optional_)

  Filename must use `release_v<MOD_VERSION>.png` format

  When `MOD_VERSION` is set to `1.207`, expected filename is `release_v1.207.png`

- Run Actions -> [Schedule](../../../actions/workflows/schedule.yml) workflow with following options, and wait until it finishes

  - `Release candidate`: `true`

  - `Push results`: `true`

- Run Actions -> [Package](../../../actions/workflows/package.yml) workflow with following options, and wait until it finishes

  - `Release`: `true` (if `false`, prerelease will be created)

- Open newly created [release](../../../releases) draft and copy NMA-formatted changelog

  You can use either copy button in top-right corner of changelog, or release edit page

- Tweak and publish newly created [release](../../../releases) draft

  Horizontal line marks the end of actual release body

  Remember to remove it and everything below

- Update [NMA thread](https://nma-fallout.com/threads/218045/)

  Paste previously copied changelog as starting point for your post

- ???

- Profit
