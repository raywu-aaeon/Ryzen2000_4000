#;******************************************************************************
#;* Copyright (c) 2018, Aaeon Corporation. All Rights Reserved.
#;*
#;* You may not reproduce, distribute, publish, display, perform, modify, adapt,
#;* transmit, broadcast, present, recite, release, license or otherwise exploit
#;* any part of this publication in any form, by any means, without the prior
#;* written permission of Aaeon Corporation.
#;*
#;******************************************************************************
#; ModuleName:
#;
#;   AutoGenAaeonDefaultPwd.gawk
#;
#;------------------------------------------------------------------------------
#;
#; Abstract:
#;
#;   A gawk co-works with AutoGenAaeonDefaultPwd.mak to produce Build/AutoGenAaeonDefaultPwd.uni automatically
#;

BEGIN {
    print "/=#" > "Build/AutoGenAaeonDefaultPwd.uni"
    print "#include \"VFR.uni\"" > "Build/AutoGenAaeonDefaultPwd.uni"
    print "//----------------------------------------------------------------------------" > "Build/AutoGenAaeonDefaultPwd.uni"
    print "// AAEON DefaultPwd" > "Build/AutoGenAaeonDefaultPwd.uni"
    print "//----------------------------------------------------------------------------" > "Build/AutoGenAaeonDefaultPwd.uni"
    print "" > "Build/AutoGenAaeonDefaultPwd.uni"
    print "// Enable/Disable default password override" > "Build/AutoGenAaeonDefaultPwd.uni"
    print "#string STR_AAEON_SET_DEFAULT_ADMIN_PWD                    #language eng \"Default Admin Password Override\"" > "Build/AutoGenAaeonDefaultPwd.uni"
    print "#string STR_AAEON_SET_DEFAULT_ADMIN_PWD_HELP               #language eng \"Enable/Disable default Admin password override.\"" > "Build/AutoGenAaeonDefaultPwd.uni"
    print "#string STR_AAEON_SET_DEFAULT_USER_PWD                     #language eng \"Default User Password Override\"" > "Build/AutoGenAaeonDefaultPwd.uni"
    print "#string STR_AAEON_SET_DEFAULT_USER_PWD_HELP                #language eng \"Enable/Disable default User password override.\"" > "Build/AutoGenAaeonDefaultPwd.uni"
    print "#string STR_AAEON_ENABLED_STRING                           #language en-US \"Enabled\"" > "Build/AutoGenAaeonDefaultPwd.uni"
    print "#string STR_AAEON_DISABLED_STRING                          #language en-US \"Disabled\"" > "Build/AutoGenAaeonDefaultPwd.uni"
    print "" > "Build/AutoGenAaeonDefaultPwd.uni"
    print "#string STR_AAEON_SET_DEFAULT_PWD_AT_FIRST_BOOT            #language eng \"Set Default Password at First Boot\"" > "Build/AutoGenAaeonDefaultPwd.uni"
    print "#string STR_AAEON_SET_DEFAULT_PWD_AT_FIRST_BOOT_HELP       #language eng \"A flag to judge if default password was overridden\"" > "Build/AutoGenAaeonDefaultPwd.uni"
    print "" > "Build/AutoGenAaeonDefaultPwd.uni"
    print "// Modify STR_AAEON_DEFAULT_XXX_PWD_VALUE to override default password " > "Build/AutoGenAaeonDefaultPwd.uni"
    print "#string STR_AAEON_DEFAULT_ADMIN_PWD                        #language eng \"Set Default Admin Password: (Limitation of length is 20)\"" > "Build/AutoGenAaeonDefaultPwd.uni"    
    print "#string STR_AAEON_DEFAULT_USER_PWD                         #language eng \"Set Default User Password: (Limitation of length is 20)\"" > "Build/AutoGenAaeonDefaultPwd.uni"

    close("Build/AutoGenAaeonDefaultPwd.uni")
}
