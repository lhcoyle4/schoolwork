module controlbar(LEDR, KEY, CLOCK_50);
  input [3:0] KEY;
  input CLOCK_50;
  output reg [17:0] LEDR;
  reg [25:0] counter;
  reg button_held;

  initial begin
    button_held = 0;
    counter = 0;
    LEDR = 0;
  end

  always @ (posedge CLOCK_50) begin
  
    //no buttons are currently pressed
    if (!button_held) begin  
    
      //so, if '-' pressed, must shrink bar immediately
      if (!KEY[3]) begin      
        button_held <= 1;
        //shrink LEDR bar
        LEDR <= LEDR << 1;   
      end
      
      //or, if '+' pressed, must grow bar immediately
      else if (!KEY[2]) begin 
        button_held <= 1;
        
        //grow LEDR bar
        if (LEDR == 0) begin
          LEDR[17] <= 1;
        end

        else begin
          LEDR <= LEDR | (LEDR >> 1);
        end
      end

    end
    
    //a button is being held down
    else begin
    
      //so, if '-' held, wait 1s to shrink bar
      if (!KEY[3]) begin      
        button_held <= 1;
        counter <= counter + 1;
        //shrink LEDR bar after 1 second
        if (counter > 50000000) begin          
          LEDR <= LEDR << 1; 
          counter <= 0;
        end
      end
      
      //or, if '+' held, wait 1s to grow bar
      else if (!KEY[2]) begin 
        button_held <= 1;
        counter <= counter + 1;
        //grow LEDR bar after 1 second
        if (counter > 50000000) begin
        
          if (LEDR == 0) begin
            LEDR[17] <= 1;
          end

          else begin
            LEDR <= LEDR | (LEDR >> 1);
          end
          
          counter <= 0;
        end 
      end
      
      //else, prepare to respond immediately to next press
      else begin             
        button_held <= 0;
        counter <= 0;
      end

    end

  end

endmodule