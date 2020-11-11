library verilog;
use verilog.vl_types.all;
entity forwardingWBtoD is
    port(
        rs1             : in     vl_logic_vector(4 downto 0);
        rs2             : in     vl_logic_vector(4 downto 0);
        mem_wb_rd       : in     vl_logic_vector(4 downto 0);
        mem_wb_regwrite : in     vl_logic;
        rd_to_rs1       : out    vl_logic;
        rd_to_rs2       : out    vl_logic
    );
end forwardingWBtoD;
