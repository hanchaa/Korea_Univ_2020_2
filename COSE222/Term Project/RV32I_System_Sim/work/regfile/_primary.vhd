library verilog;
use verilog.vl_types.all;
entity regfile is
    port(
        clk             : in     vl_logic;
        we              : in     vl_logic;
        rs1             : in     vl_logic_vector(4 downto 0);
        rs2             : in     vl_logic_vector(4 downto 0);
        rd              : in     vl_logic_vector(4 downto 0);
        rd_data         : in     vl_logic_vector(31 downto 0);
        rs1_data        : out    vl_logic_vector(31 downto 0);
        rs2_data        : out    vl_logic_vector(31 downto 0)
    );
end regfile;
