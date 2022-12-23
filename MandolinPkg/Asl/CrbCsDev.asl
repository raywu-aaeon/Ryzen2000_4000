#define LPC0 SBRG

Scope(\_SB.PCI0){
           
			Scope(GPP1)
			{
				Method(RHRS, 0, NotSerialized)
				{
					Name(RBUF, ResourceTemplate()
					{
						GpioInt(Edge, ActiveLow, ExclusiveAndWake, PullNone, 0x0000, "\\_SB.GPIO", 0x00, ResourceConsumer,,)
						{
							0x000E
						}
						GpioInt(Edge, ActiveHigh, SharedAndWake, PullNone, 0x0000, "\\_SB.GPIO", 0x00, ResourceConsumer,,)
						{
							0x00AC
						}
					})
					Return(RBUF)
				}

			} 
			Scope(GPP1.DEV0)
			{
			  Name(_S0W, 0x04)
			}


			Scope(GPP2)
			{
				Method(RHRS, 0, NotSerialized)
				{
					Name(RBUF, ResourceTemplate()
					{
						GpioInt(Edge, ActiveLow, ExclusiveAndWake, PullNone, 0x0000, "\\_SB.GPIO", 0x00, ResourceConsumer,,)
						{
							0x0002
						}
						GpioInt(Edge, ActiveHigh, SharedAndWake, PullNone, 0x0000, "\\_SB.GPIO", 0x00, ResourceConsumer,,)
						{
							0x00AC
						}
					})
					Return(RBUF)
				}
			} 
			Scope(GPP2.BCM5)
			{
			     Name(_S0W, 0x04)
			}
		        Scope(GPP6.NVME)
		        {
			     Name(_S0W, 0x04)
		        }
} // end of PCI0 
