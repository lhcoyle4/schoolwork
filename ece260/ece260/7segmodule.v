module toy(LEDR, SW, HEX0);
    output reg [17:0] LEDR;
   output reg [6:0] HEX0;
    input [17:0] SW;

    always @ (SW) begin
    case(SW[3:0])
        0: HEX0 = 7'b1000000;
        1: HEX0 = 7'b1111001;
        2: HEX0 = 7'b0100100;
        3: HEX0 = 7'b0110000;
        4: HEX0 = 7'b0011001;
        5: HEX0 = 7'b0010010;
        6: HEX0 = 7'b0000011;
        7: HEX0 = 7'b1111000;
        8: HEX0 = 7'b0000000;
        9: HEX0 = 7'b0011000;
       10: HEX0 = 7'b0001000;
       11: HEX0 = 7'b0000011;
       12: HEX0 = 7'b1000110;
       13: HEX0 = 7'b0100001;
       14: HEX0 = 7'b0000110;
       15: HEX0 = 7'b0001110;
     endcase 
   end
endmodule