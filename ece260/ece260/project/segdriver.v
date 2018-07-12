/*****************************************************************************/
/*!
* \file   segdriver.v
* \author Louis Coyle II
* \par    email: louis.coyleii\@digipen.edu
* \par    DigiPen login: louis.coyleii
* \par    Course: ECE260
* \par    Final Project
* \date   04/17/14
* 
* \brief
* This file contains the implementation of the segdriver module for the final
* project.
*
* Hours spent on this section: 0 - 1.
*/
/*****************************************************************************/

module segdriver(decimal_in, seg);
	 output reg [6:0] seg;
    input wire [3:0] decimal_in;

    always @ (decimal_in) begin
		case(decimal_in)
		    0: seg = 7'b1000000;
		    1: seg = 7'b1111001;
		    2: seg = 7'b0100100;
		    3: seg = 7'b0110000;
		    4: seg = 7'b0011001;
		    5: seg = 7'b0010010;
		    6: seg = 7'b0000010;
		    7: seg = 7'b1111000;
		    8: seg = 7'b0000000;
		    9: seg = 7'b0011000;
		   10: seg = 7'b0001000;
		   11: seg = 7'b0000011;
		   12: seg = 7'b1000110;
		   13: seg = 7'b0100001;
		   14: seg = 7'b0000110;
		   15: seg = 7'b0001110;
		 endcase 
	 end
endmodule