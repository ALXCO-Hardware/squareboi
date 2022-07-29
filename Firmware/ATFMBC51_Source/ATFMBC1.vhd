library IEEE;
use IEEE.std_logic_1164.all;


--MBC 5 + 1 replacement code
--For use only with Squareboi V2.01
--Check pin assignments before compiling!!!!
--ALXCO 2022



entity ATFMBC1 is
	Port(
		GBCLK	   : in  std_ulogic; --Route to a clock
		RESET_N  : in  std_ulogic; --Route to GCLR
		RD_N     : in  std_ulogic;
		WR_N     : in  std_ulogic; --Route to a clock
		CS_N     : in  std_ulogic;
		MBCMODE  : in  std_ulogic; -- Mode 0 indicates MBC5. Mode 1 indicates MBC1
		A        : in  std_ulogic_vector(15 downto 12);
		D        : in  std_ulogic_vector(7 downto 0);
		TP44		: in  std_ulogic; -- Unused, mandatory input so held at ground

		
		
		RA       : out std_ulogic_vector(22 downto 14);
		AA       : out std_ulogic_vector(14 downto 13);
		RAM_CS_N : out std_ulogic;
		TP40		: out std_ulogic -- Debug output

	);
end entity ATFMBC1;

architecture Behavioral of ATFMBC1 is
	
signal ram_enable_r : std_ulogic;
signal rom_bank_r   : std_ulogic_vector(8 downto 0);
signal ram_bank_r   : std_ulogic_vector(1 downto 0);
signal bankmode_r   : std_ulogic;
signal mbcmode_r	  : std_ulogic; -- Mode 0 indicates MBC5. Mode 1 indicates MBC1. Stores contents of MBCMODE pin at startup.
signal mbclocked_r  : std_ulogic;

begin

-----------------------------------------------------------------------
-- Signal Assignments
-----------------------------------------------------------------------


--RAMCSN is asserted if 4 conditions are met:
--the gameboy's CS pin is low
--we're in the RAM address space (A000-BFFF), done by checking the first 3 bits of the address
--the ram enable register contains a 1
--we're not in reset 
--And one extra condition, for compatibility with FRAM!
--If GBCLK is high, we hold RAMCSN high, to allow for a re-charge between operations
--this is relevant for games that use cartridge ram as work ram and do multiple reads in a row
RAM_CS_N <= '0' when (CS_N = '0' and A(15 downto 13) = "101" and ram_enable_r = '1' and RESET_N = '1' and GBCLK = '0') else
            '1';

-- RAM address is always passed through, unless we're specifically using an MBC1 in mode 0 (no ram banking)
-- AND within the ram address space.	

			
AA(14 downto 13) <= "00" when (A(15 downto 13) = "101" and bankmode_r = '0' and mbcmode_r = '1') else
                    ram_bank_r;				
				

--Rom Address receives 0 when we're not using banking, or in reset.
--otherwise it receives the contents of the internal rom register, correcting bank 0 to bank 1
--This is still susceptible to the bank 20 40 60 bug
--ie those banks cannot be accessed on an MBC1 unless we're using mode 0	

--ROM Address receives 0 when we're not using banking, or in reset.
--otherwise, it is divided into 3 areas

--bits 22 and 21:
--only relevant on MBC5, receive rom_bank_r(8 downto 7)
--on MBC1, should always just be 0, since it can't handle ROM sizes above 2MB

--bits 20 and 19:
--	on MBC5, receive rom_bank_r(6 downto 5)
-- on MBC1, if (banking mode is 0 AND A(14)=1) OR (banking mode is 1), receive ram_bank_r, otherwise receive 00

--bits 18-14:
-- on MBC5, always receive contents of rom_bank_r
-- on MBC1, receive rom_bank_r when it's not 00000, otherwise receive 00001 

RA(22 downto 21) <= "00"    when (A(14) = '0' or RESET_N = '0') else
                    rom_bank_r(8 downto 7);

RA(20 downto 19) <= "00" when RESET_N = '0' else
						  "00" when (bankmode_r = '0' and A(14) = '0') else	
						  rom_bank_r(6 downto 5) when mbcmode_r = '0' else
						  ram_bank_r;

RA(18 downto 14) <= "00000"    when (A(14) = '0' or RESET_N = '0') else
                    rom_bank_r(4 downto 0) when (mbcmode_r = '0' or rom_bank_r(4 downto 0) /= "00000") else
                    "00001";
						  
		

--debug output, currently outputs the inverted clock for a sanity check
--not used by any other components, feel free to implement whatever debug signals you want with it
TP40 <= not GBCLK; 			  



-----------------------------------------------------------------------
-- Sequential part
-----------------------------------------------------------------------

--Writing to specific addresses on the 0x0000-0x7FFF range (ie ROM range, where writing would not have an effect)
--will actually write to specific registers on the MBC
--Only the top 3 (4 on MBC5) bits of the address matter!
--ie A15-A14-A13 or A15-A14-A13-A12

--MBC1:
--0000-1FFF - top 3 bits 000: RAM ENABLE 
--is set to 1 when 0xA is written to D0-D3, when we want to use RAMCS

--2000-3FFF - top 3 bits 001: ROM bank 
--receives D0-D5 to indicate the rom bank in use 

--4000-5FFF - top 3 bits 010: RAM bank / ext. ROM bank  
--receives D0-D1 to indicate the ram bank in use (on mode 1), or an extra 2 bits for rom banking (on mode 0)

--6000-7FFF:  top 3 bits 011: Banking mode register 
--receives D0 to indicate the banking mode	
	

	
--MBC5:
--0000-1FFF - top 4 bits 000X: RAM ENABLE 
--is set to 1 when 0xA is written to D0-D7, when we want to use RAMCS

--2000-2FFF - top 4 bits 0010: ROM bank, lower 8 bits
--receives D0-D7 to indicate the rom bank in use

--3000-3FFF - top 4 bits 0011: ROM bank, upper bit 
--receives D0 to indicate the top bit of the rom bank in use (RA22)

--4000-5FFF - top 4 bits 010X: RAM bank 
--receives D0-D1 to indicate RAM bank in use





updateregisters_p : process(
	RESET_N,
	WR_N,
	MBCMODE
	)
begin

	if (RESET_N = '0') then -- if we're in reset, asynchronously clear all the registers
		ram_enable_r <= '0';
		rom_bank_r <= "000000000";
		ram_bank_r <= "00";
		bankmode_r <= '0';
		mbcmode_r <= '0';
		mbclocked_r <= '0';
		
		
	elsif rising_edge(WR_N) then
		-- on the first clock, lock MBCMODE so it doesn't break if the switch is bumped
		if mbclocked_r = '0' then
			mbcmode_r <= MBCMODE;
			mbclocked_r <= '1';
		end if;
		
		case (A(15 downto 13)) is
		when "000" => 
			if ((mbcmode_r = '1' and D(3 downto 0) = "1010") or (mbcmode_r = '0' and D(7 downto 0) = "00001010")) then
				ram_enable_r <= '1'; 
			else 
				ram_enable_r <= '0'; 
			end if;
			

		when "001" => 
			if (mbcmode_r = '1') then
				rom_bank_r(4 downto 0) <= D(4 downto 0);
			else
				if A(12) = '0' then
					rom_bank_r(7 downto 0) <= D;
				else
					rom_bank_r(8) <= D(0);
				end if;
			end if;
		

		when "010" => 
			ram_bank_r <= D(1 downto 0);
				
		
		when "011" => 
			if (mbcmode_r = '1') then 
				bankmode_r <= D(0);
			end if;
		
		
		when others => null; --implied that when one is not chosen, its value is maintained
		end case;
	
	end if;

end process updateregisters_p;



end architecture Behavioral;