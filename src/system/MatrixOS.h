#pragma once
#include "../framework/Classes.h"

namespace MatrixOS
{
  namespace SYS
  {
    void Init();
    uint32_t GetTick();
    uint32_t millis();
    int Execute(uint32_t addr);
    // void Beep(int intervalMs);
    void DelayMs(int intervalMs);
    void Reboot();
    void Bootloader();

    enum class EAttribute {
      DeviceType, DeviceVersion, DerviceRevision, DeviceBatch, SerialNumber,
      VelocityRange,
      LEDType, LEDSizeX, LEDSizeY, 
      BootloaderVersion, SystemVersion, 
      };
  
    uintptr_t GetAttribute(EAttribute eInternal);
    uint8_t SetAttribute(EAttribute eInternal, uint32_t value);
  }

  namespace LED
  {
    void SetRGB(CPoint xy, Colour colour, uint8_t layer = 0);
    void Fill(Colour color, uint8_t layer = 0);
    void Render(uint8_t layer = 0);
  }

  // namespace UI
  // {
  //   void textScroll(char ascii[], Colour colour, uint8_t speed = 10, bool loop = false, uint8_t length = 0);
  //   void renderAsciiChar(char ascii, CPoint xy, Colour colour);
  //   void renderHalfHeightNum(uint16_t num, CPoint xy, Colour colour);
  //   // void renderHalfHeightDigit(uint8_t num, CPoint xy, Colour colour);
  //   uint8_t binary8bitInput(uint8_t currentNum, CPoint xy, Colour colour);
  //   uint8_t simple8bitInput(uint8_t currentNum, CPoint xy, Colour colour);
  // }

  namespace KeyPad
  {
    enum EKeyStates {IDLE, PRESSED, ACTIVED,/* HOLD, HOLD_ACTIVED,*/ RELEASED, /*HOLD_RELEASED*/};

    struct KeyInfo {
      EKeyStates state = IDLE;
      uint32_t activeTime = 0;
      uint16_t velocity = 0;
      bool changed = false; //for Pressed,Hold, RELEASED, AFTERTOUCH
      bool hold = false;
      uint32_t holdTime()
      {
        if(state == IDLE)
        return 0;

        if(activeTime > millis())
        return 0;

        return millis() - activeTime;
      }
      operator bool() { return velocity > 0; }
    };

    void Scan();
    void SetHandler(void (*f)(KeyInfo));
    void ClearHandler();
    KeyInfo GetKey(CPoint keyID);
  }

  namespace DBG
  {
    void Print (const char* format, ...);
  }

  // namespace MEMORY
  // {
  //   const int SharedBufferSize = 2048+128;

  //   void SetSharedBuffer(void*);
  //   void* GetSharedBuffer();

  //   void LinearStart();
  //   bool LinearFinish();
  //   bool LinearProgram( uint32_t nAddress, unsigned char* pData, int nLength );
  // }

  // namespace FAT
  // {
  //   enum EIoMode {
  //     IoRead = 1,
  //     IoWrite = 2,
  //     IoClosed = 3
  //   };

  //   enum EResult 
  //   {
  //     EOk,
  //     EDiskError,
  //     EIntError,
  //     ENoFile,
  //     ENoPath,
  //     EDiskFull
  //   };

  //   enum EAttribute 
  //   {
  //     EReadOnly = 1,
  //     EHidden = 2,
  //     ESystem = 4,
  //     EDirectory = 0x10,
  //     EArchive = 0x20
  //   };

  //   struct TFindFile
  //   {
  //     uint32_t nFileLength;
  //     uint16_t nDate;
  //     uint16_t nTime;
  //     uint8_t nAtrib;
  //     char strName[13];
  //   };

  //   const int SectorSize = 4096;
  //   const int SectorCount = 2048;

  //   const int SharedBufferSize = SectorSize;

  //   void SetSharedBuffer(void*);
  //   void* GetSharedBuffer();

  //   EResult Init();
  //   EResult Open(const char* strName, uint8_t nIoMode);
  //   EResult Read(uint8_t* pSectorData);
  //   EResult Write(uint8_t* pSectorData);
  //   EResult Seek(uint32_t lOffset);
  //   EResult Close(int nSize);
  //   EResult Close();
  //   uint32_t GetFileSize();
	
  //   EResult OpenDir(char* strPath);
  //   EResult FindNext(TFindFile* pFile);
  // }

  // namespace OS
  // {
  //   typedef void (*TInterruptHandler)(void);
  //   enum EInterruptVector {
  //     IStackTop, IReset, INMIException, IHardFaultException, IMemManageException, 
  //     IBusFaultException, IUsageFaultException, _Dummy1, _Dummy2,
  //     _Dummy3, _Dummy4, ISVC, IDebugMonitor, _Dummy5, IPendSVC, 
  //     ISysTick, IWWDG_IRQ, IPVD_IRQ, ITAMPER_IRQ, IRTC_IRQ, IFLASH_IRQ,
  //     IRCC_IRQ, IEXTI0_IRQ, IEXTI1_IRQ, IEXTI2_IRQ, IEXTI3_IRQ, IEXTI4_IRQ,
  //     IDMA1_Channel1_IRQ, IDMA1_Channel2_IRQ, IDMA1_Channel3_IRQ,
  //     IDMA1_Channel4_IRQ, IDMA1_Channel5_IRQ, IDMA1_Channel6_IRQ,
  //     IDMA1_Channel7_IRQ, IADC1_2_IRQ, IUSB_HP_CAN_TX_IRQ, 
  //     IUSB_LP_CAN_RX0_IRQ, ICAN_RX1_IRQ, ICAN_SCE_IRQ, IEXTI9_5_IRQ,
  //     ITIM1_BRK_IRQ, ITIM1_UP_IRQ, ITIM1_TRG_COM_IRQ, ITIM1_CC_IRQ,
  //     ITIM2_IRQ, ITIM3_IRQ, ITIM4_IRQ, II2C1_EV_IRQ, II2C1_ER_IRQ,
  //     II2C2_EV_IRQ, II2C2_ER_IRQ, ISPI1_IRQ, ISPI2_IRQ, IUSART1_IRQ,
  //     IUSART2_IRQ, IUSART3_IRQ, IEXTI15_10_IRQ, IRTCAlarm_IRQ, 
  //     IUSBWakeUp_IRQ, ITIM8_BRK_IRQ, ITIM8_UP_IRQ, ITIM8_TRG_COM_IRQ,
  //     ITIM8_CC_IRQ, IADC3_IRQ, IFSMC_IRQ, ISDIO_IRQ, ITIM5_IRQ,
  //     ISPI3_IRQ, IUART4_IRQ, IUART5_IRQ, ITIM6_IRQ, ITIM7_IRQ,
  //     IDMA2_Channel1_IRQ, IDMA2_Channel2_IRQ, IDMA2_Channel3_IRQ,
  //     IDMA2_Channel4_5_IRQ };

  //   void SetArgument(char* argument);
  //   char* GetArgument();
  //   bool HasArgument();
  //   TInterruptHandler GetInterruptVector(EInterruptVector);
  //   void SetInterruptVector(EInterruptVector, TInterruptHandler);
  //   uint32_t DisableInterrupts();
  //   void EnableInterrupts(uint32_t);
  // }

  namespace USB
  {
    typedef void (*THandler)(void);

    void Enable();
    void Initialize(void* pDeviceInfo, void* pDevice, void* pDeviceProperty, void* pUserStandardRequests,
      THandler arrHandlerIn[], THandler arrHandlerOut[], THandler arrCallbacks[], THandler leaveLowPowerMode);
    void InitializeMass();
    void Disable();

    void InitializeFinish(int msk);
  }

  // namespace GPIO
  // {
  //   enum EPin {P1, P2, P3, P4, P5, P6, P7, P8};
  //   enum EMode {Input = 1, Output = 2, Pwm = 4, PullUp = 8, PullDown = 16, I2c = 32, Uart = 64};
  //   const int AnalogRange = 1024;

  //   void DigitalWrite(EPin pin, bool value);
  //   bool DigitalRead(EPin pin);
  //   void AnalogWrite(EPin pin, int value);
  //   int AnalogRead(EPin pin);
  //   void PinMode(EPin pin, EMode mode);

  //   namespace I2C          
  //   {
  //     bool BeginTransmission(uint8_t address);
  //     bool RequestFrom(uint8_t address, uint8_t bytes);
  //     bool Write(uint8_t data);
  //     uint8_t Read();
  //     bool EndTransmission(bool stop = true);
  //   }

  //   namespace UART
  //   {
  //     enum EConfig {length8 = 0, length9 = 0x10, stopBits1 = 0, stopBits15 = 0x1, stopBits2 = 0x2,
  //       parityNone = 0, parityEven = 0x4, parityOdd = 0x08, flowNone = 0, flowHw = 0x20};
  //     enum EConfigMask {length = EConfig::length8 | EConfig::length9, stopBits = EConfig::stopBits1 | EConfig::stopBits15 |
  //         EConfig::stopBits2, parity = EConfig::parityNone | EConfig::parityEven | EConfig::parityOdd, flow = EConfig::flowNone | EConfig::flowHw
  //     };
  //     void Setup(int baudrate, EConfig config);
  //     bool Available();
  //     uint8_t Read();
  //     void Write(uint8_t);
  //   }
  }
}