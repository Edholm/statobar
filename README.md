statobar
==========
This is an alternative to Conky that I wrote as an exercise in C++. Saves me a few CPU cycles compared to Conky and gives me more customizability.

## Compile & install
Note that this depends on Boost and will crash if you do not have bluez installed and started

``` bash
$ git clone https://github.com/Edholm/statobar.git
```
Make the necessary changes in the header files. Wlan interface name etc.

```
$ cd statobar
$ make
$ cp bin/statobar ~/.i3
```

## How to use
In your i3 config, put this in the `bar` section:

```
status_command    $HOME/.i3/statobar
```

then restart i3: 
```bash
$ i3-msg restart
```

## Result:
This would result in something like this:

![Result](screenshots/bar.png "Result")  
![Result2](screenshots/bar2.png "Result2")  
