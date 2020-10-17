library verilog;
use verilog.vl_types.all;
entity aludec is
    port(
        opcode          : in     vl_logic_vector(6 downto 0);
        funct7          : in     vl_logic_vector(6 downto 0);
        funct3          : in     vl_logic_vector(2 downto 0);
        alucontrol      : out    vl_logic_vector(4 downto 0)
    );
end aludec;
