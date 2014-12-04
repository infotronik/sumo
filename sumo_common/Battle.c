/*
 * Battle.c
 *
 *  Created on: 26.09.2014
 *      Author: marc
 */

#include "Platform.h"
#include "Application.h"




#if PL_HAS_SHELL
/*!
 * \brief Prints the system low power status
 * \param io I/O channel to use for printing status
 */
static void BATTLE_PrintStatus(const CLS1_StdIOType *io) {
  //TACHO_CalcSpeed(); /* only temporary until this is done periodically */
  CLS1_SendStatusStr((unsigned char*)"Tache", (unsigned char*)"\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  L speed", (unsigned char*)"", io->stdOut);
  CLS1_SendNum32s(TACHO_GetSpeed(TRUE), io->stdOut);
  CLS1_SendStr((unsigned char*)" steps/sec\r\n", io->stdOut);
  CLS1_SendStatusStr((unsigned char*)"  R speed", (unsigned char*)"", io->stdOut);
  CLS1_SendNum32s(TACHO_GetSpeed(FALSE), io->stdOut);
  CLS1_SendStr((unsigned char*)" steps/sec\r\n", io->stdOut);
}

/*!
 * \brief Prints the help text to the console
 * \param io I/O channel to be used
 */
static void BATTLE_PrintHelp(const CLS1_StdIOType *io) {
  CLS1_SendHelpStr((unsigned char*)"tacho", (unsigned char*)"Group of tacho commands\r\n", io->stdOut);
  CLS1_SendHelpStr((unsigned char*)"  help|status", (unsigned char*)"Shows tacho help or status\r\n", io->stdOut);
}

uint8_t BATTLE_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io) {
  if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP)==0 || UTIL1_strcmp((char*)cmd, (char*)"tacho help")==0) {
    TACHO_PrintHelp(io);
    *handled = TRUE;
  } else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS)==0 || UTIL1_strcmp((char*)cmd, (char*)"tacho status")==0) {
    TACHO_PrintStatus(io);
    *handled = TRUE;
  }
  return ERR_OK;
}
#endif /* PL_HAS_SHELL */

void TACHO_Deinit(void) {
}

void BATTLE_Init(void) {

}

#endif /* PL_HAS_MOTOR_TACHO */
