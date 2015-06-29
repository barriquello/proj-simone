
#define KEYB_CHANNEL		 10
#define AD_KEY_RANGE		 50	// 0,04V @ (3,3V, 12 bits)

#define ENTER_KEY          	 (INT8U)11
#define CANCEL_KEY         	 (INT8U)12
#define UP_KEY         		 (INT8U)13
#define DOWN_KEY         	 (INT8U)14
#define LEFT_KEY         	 (INT8U)15
#define RIGHT_KEY         	 (INT8U)16
#define NO_KEY             	 (INT8U)255

#define UP_KEY_L           	 (INT16U)(1009 - AD_KEY_RANGE)
#define UP_KEY_H             (INT16U)(1009 + AD_KEY_RANGE)
#define DOWN_KEY_L           (INT16U)(561 - AD_KEY_RANGE)
#define DOWN_KEY_H           (INT16U)(561 + AD_KEY_RANGE)
#define LEFT_KEY_L           (INT16U)(278 - AD_KEY_RANGE)
#define LEFT_KEY_H           (INT16U)(278 + AD_KEY_RANGE)
#define RIGHT_KEY_L          (INT16U)(807 - AD_KEY_RANGE)
#define RIGHT_KEY_H          (INT16U)(807 + AD_KEY_RANGE)
#define ENTER_KEY_L          (INT16U)(1188 - AD_KEY_RANGE)
#define ENTER_KEY_H          (INT16U)(1188 + AD_KEY_RANGE)
#define CANCEL_KEY_L         (INT16U)0
#define CANCEL_KEY_H         (INT16U)AD_KEY_RANGE


INT8U FindKey(INT16U ADLevel);

