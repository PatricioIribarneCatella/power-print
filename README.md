# Power Print

Prints information about the status of the power supply (battery).

## Configuration

It needs a configuration file named **.power_print.conf** located in *HOME* directory. In this file the path to the power supply information has to be put in. Usualy this location is in `/sys/class/power_supply/BATNAME/uevent`, where _BATNAME_ is the name of the battery. For example you can do:

```bash
 $ touch $HOME/.power_print.conf

 $ echo "PATH=/sys/class/power_supply/BATNAME/uevent" >> $HOME/.power_print.conf
```

### Compile

```bash
 $ make
```

### Run

```bash
 $ make run
```

