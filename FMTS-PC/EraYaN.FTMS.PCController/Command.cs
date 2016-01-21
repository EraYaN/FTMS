using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EraYaN.FTMS.PCController
{
    public enum Command : byte
    {
        //Control codes
        OK = 0xF0,
        Reset = 0xF1,
        Refresh = 0xF2,
        Forbidden = 0xF3,
        NotFound = 0xF4,
        TypeMismatch = 0xF5,
        VersionUnsupported = 0xFE,
        Unsupported = 0xFF,
        //Int16 commands
        SetInteger16 = 0x13,
        GetInteger16 = 0x15,
        //Int32 commands
        SetInteger32 = 0x23,
        GetInteger32 = 0x25,
        //Boolean commands
        SetBoolean = 0x33,
        GetBoolean = 0x35,
        //Float commands
        SetFloat = 0x43,
        GetFloat = 0x45,
        //String commands
        SetString = 0x53,
        GetString = 0x55,
        //Function commands
        DisplayString = 0xE5,
        Debug = 0xE6,

        
    }
}
