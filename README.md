# dottracker

**dottracker** is a tracking program for UNIX dotfiles and configurations.

## Build

```bash
# Clone the repository
git clone git@github.com/andreagiorgino/dottracker
cd dottracker

# Build the project
./build.sh

# Install the binary to local path
ln -fs $(realpath build/dottracker) $HOME/.local/bin
```

> [!IMPORTANT]
> Make sure that `~/.local/bin` exists and that it is part of `$PATH` if
> you want to install the binary whit the above method

## Configuration

```bash
mkdir ~/.config/dottracker
cd ~/.config/dottracker

touch files.conf
mkdir archive
```

```bash
# ~/.bashrc

export DOTTRACKER_CONFIG="${HOME}/.config/dottracker/files.conf"
export DOTTRACKER_ARCHIVE="${HOME}/.config/dottracker/archive"
```

## Usage

```bash
dottracker [-v | --version] [-h | --help] <command> [<args>]
```

### Commands

Name        | Description                                        | Arguments          | Options
:---------- | :------------------------------------------------- | :----------------- | :-------
`diff`      | Print a diff of the tracked files                  | -                  | `[<-s \| --source> <file_path>]`
`untracked` | Print a list of the archived and not tracked files | -                  | `[<-s \| --source> <file_path>]`<br/>`[--delete]`
`update`    | Update files in target                             | `local`, `archive` | `[<-s \| --source> <file_path>]`
