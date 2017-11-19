#ifndef EH_SIM_DATA_SHEET_ENERGY_HPP
#define EH_SIM_DATA_SHEET_ENERGY_HPP

namespace ehsim {

// all energy units are in nJ

// Mementos numbers are for an MSP430F1232 (http://www.ti.com/product/msp430f1232)
// see: https://www.usenix.org/legacy/event/hotpower08/tech/full_papers/ransford/ransford_html/
constexpr uint32_t MEMENTOS_CPU_FREQUENCY = 8000000;
constexpr double MEMENTOS_CAPACITANCE = 10e-6;
constexpr double MEMENTOS_MAX_CAPACITOR_VOLTAGE = 4.5;
constexpr double MEMENTOS_INSTRUCTION_ENERGY = 2.0;
// memory naming scheme is MEMENTOS_DESTINATION_SOURCE
constexpr double MEMENTOS_REG_REG = 1.1;
constexpr double MEMENTOS_REG_FLASH = 5.2;
constexpr double MEMENTOS_REG_MEM = 6.3;
constexpr double MEMENTOS_MEM_REG = 8.1;
constexpr double MEMENTOS_MEM_FLASH = 11.8;
constexpr double MEMENTOS_MEM_MEM = 11.7;
constexpr double MEMENTOS_FLASH_REG = 461.0;
constexpr double MEMENTOS_FLASH_FLASH = 350.3;
constexpr double MEMENTOS_FLASH_MEM = 1126.2;

// Batteryless Sim numbers are from: https://github.com/PERSISTLab/BatterylessSim/
constexpr double BATTERYLESS_CAPACITANCE = 10e-6;
constexpr double BATTERYLESS_MAX_CAPACITOR_VOLTAGE = 7.5;

// NVP numbers from Architecture Exploration for Ambient Energy Harvesting Nonvolatile Processors
// see Section 3 from paper - 8 KHz clock frequency
constexpr uint32_t NVP_CPU_FREQUENCY = 8000;
// see Section V from paper - capacitor used in the system is 470 nF
constexpr double NVP_CAPACITANCE = 470e-9;
// see Figure 11 from paper
constexpr auto NVP_INSTRUCTION_ENERGY = 0.03125;
constexpr auto NVP_ODAB_BACKUP_ENERGY = 0.75;
constexpr auto NVP_ODAB_RESTORE_ENERGY = 0.25;
constexpr auto NVP_BEC_BACKUP_ENERGY = 0.125;
constexpr auto NVP_BEC_RESTORE_ENERGY = 0.25;
// see Figure 10 from paper
constexpr uint64_t NVP_ODAB_BACKUP_TIME = 35;
constexpr uint64_t NVP_ODAB_RESTORE_TIME = 35;
constexpr uint64_t NVP_BEC_BACKUP_TIME = 2;
constexpr uint64_t NVP_BEC_RESTORE_TIME = 1;

// see data sheet for STM32L011K4 (M0+) at: http://eembc.org/benchmark/reports/benchreport.php
// Table 22
constexpr uint32_t CORTEX_M0PLUS_FREQUENCY = 8000000;
constexpr double CORTEX_M0PLUS_CURRENT = 1.3e-3;
constexpr double CORTEX_M0PLUS_VOLTAGE = 1.8;
// this includes the fetching of the instruction
constexpr double CORTEX_M0PLUS_INSTRUCTION_ENERGY_PER_CYCLE =
    1e9 * (CORTEX_M0PLUS_CURRENT * CORTEX_M0PLUS_VOLTAGE) / CORTEX_M0PLUS_FREQUENCY;
// Table 43 - energy per byte
constexpr double CORTEX_M0PLUS_ENERGY_FLASH = 1e9 * 0.7e-6 * 3.6 * 3.94e-3;

// based on Clank: Architectural Support for Intermittent Computation
constexpr uint64_t CLANK_BACKUP_ARCH_TIME = 40;
constexpr double CLANK_INSTRUCTION_ENERGY = CORTEX_M0PLUS_INSTRUCTION_ENERGY_PER_CYCLE;
constexpr double CLANK_BACKUP_ARCH_ENERGY = CORTEX_M0PLUS_ENERGY_FLASH * 4 * 20;
constexpr double CLANK_RESTORE_ENERGY = CORTEX_M0PLUS_ENERGY_FLASH * 4 * 20;
constexpr uint64_t CLANK_MEMORY_TIME = 2;
}

#endif //EH_SIM_DATA_SHEET_ENERGY_HPP
