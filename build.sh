#!/bin/bash

# Build script for the Physical Activities Management System
# Compatible with macOS ARM64 and x86_64

set -e  # Stop execution on error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}=== Physical Activities Management System ===${NC}"
echo -e "${BLUE}Setting up environment...${NC}"

# Check if in correct directory
if [ ! -f "imperative-c/Source.c" ]; then
    echo -e "${RED}Error: Source.c file not found!${NC}"
    echo -e "${RED}Run this script from the project root directory.${NC}"
    exit 1
fi

# Check if data files exist
echo -e "${YELLOW}Checking data files...${NC}"
for file in "customer.txt" "activity.txt" "plan.txt"; do
    if [ ! -f "imperative-c/$file" ]; then
        echo -e "${RED}Error: File $file not found!${NC}"
        exit 1
    fi
done
echo -e "${GREEN}✓ All data files found${NC}"

# Detect operating system and architecture
OS=$(uname -s)
ARCH=$(uname -m)
echo -e "${BLUE}System: $OS $ARCH${NC}"

# Compile the program
echo -e "${YELLOW}Compiling...${NC}"
if make clean > /dev/null 2>&1; then
    echo -e "${GREEN}✓ Cleanup completed${NC}"
fi

if make; then
    echo -e "${GREEN}✓ Compilation successful!${NC}"
else
    echo -e "${RED}✗ Compilation error${NC}"
    exit 1
fi

# Copy data files to execution directory
echo -e "${YELLOW}Preparing execution environment...${NC}"
cp imperative-c/*.txt . 2>/dev/null || true
echo -e "${GREEN}✓ Data files copied${NC}"

echo -e "${GREEN}=== Build Completed Successfully! ===${NC}"
echo -e "${BLUE}To run the program:${NC}"
echo -e "  ${YELLOW}./activities${NC}  or  ${YELLOW}make run${NC}"
echo
echo -e "${BLUE}Available commands:${NC}"
echo -e "  ${YELLOW}make help${NC}     - Show all commands"
echo -e "  ${YELLOW}make clean${NC}    - Remove compiled files"
echo -e "  ${YELLOW}make debug${NC}    - Compile debug version" 