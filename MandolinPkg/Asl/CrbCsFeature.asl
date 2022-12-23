//OutPut debug message to serial port.
//External(\SDBG.CON1, MethodObj)


// Picasso: Check Point out to 80 port 
Method(TPST, 1, Serialized)
{
        Add(Arg0, 0xB0000000, Local0)
        OperationRegion(VARM, SystemIO, 0x80, 0x04)
        Field(VARM, DWordAcc, NoLock, Preserve)
        {
            VARR, 32,
        }
        
       //  OutPut check point to 80 port.
       Store(Local0, VARR)
       
       //  OutPut check point to serial port.
       // If (CondRefOf(\SDBG.CON0)){
       //     \SDBG.CON1("TPST = 0x%x\n",Local0)
       // }
}

