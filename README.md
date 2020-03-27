# Power Print

Prints information about the status of the power supply (battery).

## Configuration

It follows the **XDG Base Directory** convention, so it needs a configuration file named **config** located in `HOME/.config/power-print` directory. Alternatively, you can set an _environment variable_ called **POWPRINTPATH** where the **config** file is located.

In this file the _path_ to the power supply information has to be put in. Usually this location is in `/sys/class/power_supply/BATNAME/uevent`, where _BATNAME_ is the name of the battery. For example you can do:

```bash
 $ mkdir -p $HOME/.config/power-print
 $ touch $HOME/.config/power-print/config

 $ echo "PATH=/sys/class/power_supply/BATNAME/uevent" > $HOME/.config/power-print/config
```

### Compile

```bash
 $ make
```

### Run

```bash
 $ make run
```

