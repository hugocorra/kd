kd
==

This is a small and easy to use utility that can be used to store and retrieve directories.
At the beginning, I thought it was possible to create an application that also changes the current directory, but then I realized that it's not so easy, so the application only takes care about store/retrieve directories using aliases.

E.G.:

# display the help and exit
`c:\Users\Hugo>kd --help`
`...`

# list all aliases and directories
`c:\Users\Hugo>kd -l`
`myprojects    -> C:\Users\Hugo\Development\Personal\MyProjects\`
`github        -> C:\Users\Hugo\Development\Github`
`temp          -> C:\Temp`

# create an entry
`c:\Users\Hugo>kd -a C:\Packages\boost_1_54 boost`
`c:\Users\Hugo>kd -l`
`boost         -> C:\Packages\boost_1_54`
`myprojects    -> C:\Users\Hugo\Development\Personal\MyProjects\`
`github        -> C:\Users\Hugo\Development\Github`
`temp          -> C:\Temp`

# remove an entry
`c:\Users\Hugo>kd -r temp`
`c:\Users\Hugo>kd -l`
`boost         -> C:\Packages\boost_1_54`
`myprojects    -> C:\Users\Hugo\Development\Personal\MyProjects\`
`github        -> C:\Users\Hugo\Development\Github`

# list a specific entry
`c:\Users\Hugo>kd boost`
`boost -> C:\Packages\boost_1_54`
