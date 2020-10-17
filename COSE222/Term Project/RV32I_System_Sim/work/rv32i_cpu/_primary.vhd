library verilog;
use verilog.vl_types.all;
entity rv32i_cpu is
    port(
        clk             : in     vl_logic;
        reset           : in     vl_logic;
        pc              : out    vl_logic_vector(31 downto 0);
        inst            : in     vl_logic_vector(31 downto 0);
        Memwrite        : out    vl_logic;
        Memaddr         : out    vl_logic_vector(31 downto 0);
        MemWdata        : out    vl_logic_vector(31 downto 0);
        MemRdata        : in     vl_logic_vector(31 downto 0)
    );
end rv32i_cpu;
