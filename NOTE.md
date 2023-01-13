TOKEN
	Name  = "IRQ_09_POLARITY"
	Value  = "3"
	Help  = "0 = Conforms to specifications of bus.\1 = Active High.\3 = Active Low."
	TokenType = Integer
	TargetH = Yes
	Range  = "0, 1 or 3. 2-reserved"
	Token = "IRQ_09_OVERRIDE_ENABLE" "=" "1"
End

TOKEN
    Name  = "AMI_TCG_TPM_GPIO_RESOURCE_OVERRIDE"
    Value  = "1"
    Help  = "For platforms that want to override the way TPM interrupt resources are defined"
    TokenType = Boolean
    TargetH = Yes
    TargetMAK = Yes
End

GpioInitTablePtr in AmdCpmTableOverride