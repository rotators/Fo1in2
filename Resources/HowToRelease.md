- Add great features and amazing improvements

- Update `MOD_VERSION` in [version.sh](../master/.github/workflows/scripts/version.sh)

- Upload release header to [Resources/Gallery/releases/](../../tree/master/Resources/Gallery/releases) (_optional_)

  Filename must use `release_v<MOD_VERSION>.png` format
  
  When `MOD_VERSION` is set to `1.207`, expected filename is `release_v1.207.png`

- Run Actions -> [Schedule](../../actions?query=workflow%3ASchedule) workflow with following options, and wait until it finishes

  - `Push results`: `true`

  - `Force running minor tasks`: `true`

- Run Actions -> [Package](../../actions?query=workflow%3APackage) workflow with following options, and wait until it finishes

  - `Release`: `true`

- Tweak and publish newly created [release](../../releases) draft

- Update [NMA thread](https://nma-fallout.com/threads/218045/)

- ???

- Profit
