void set_gpio_input(void *gpio_ctr, int gpio_nr) { 
	int reg_id = gpio_nr / 10; 
	int pos = gpio_nr % 10;
	uint32_t* fsel_reg = (uint32_t*) (gpio_ctr + 0x4 * reg_id);
	uint32_t fsel_val = *fsel_reg;
	uint32_t mask = 0x7 << (pos * 3);
	fsel_val = fsel_val & ~mask;
	*fsel_reg = fsel_val;
}


void set_gpio_output(void *gpio_ctr, int gpio_nr) {
	int reg_id = gpio_nr / 10;
	int pos = gpio_nr % 10;

	uint32_t* fsel_reg = (uint32_t*) (gpio_ctr + 0x4 * reg_id);
	uint32_t fsel_val = *fsel_reg;
	uint32_t mask = 0x7 << (pos * 3);
	fsel_val = fsel_val & ~mask;
	uint32_t gpio_output_select = 0x1 << (pos * 3); 
	fsel_val = fsel_val | gpio_output_select;
	*fsel_reg = fsel_val;
}

void get_gpio_input_value(void *gpio_ctr, int gpio_nr, int *value) { 
	int reg_id = gpio_nr / 32; 
	int pos = gpio_nr % 32;

	#define GPIO_LEV_OFFSET 0x34 

	uint32_t* level_reg = (uint32_t*) (gpio_ctr + GPIO_LEV_OFFSET + 0x4 * reg_id); 
	uint32_t level = *level_reg & (0x1 << pos);
	*value = level? 1:0;
}


void set_gpio_output_value(void *gpio_ctr, int gpio_nr, int value) {
	int reg_id = gpio_nr / 32;
	int pos = gpio_nr % 32;
	if(value) { 
		#define GPIO_SET_OFFSET 0x1c 
			uint32_t* output_set = (uint32_t*) (gpio_ctr + GPIO_SET_OFFSET + 0x4 * reg_id); *output_set = 0x1 << pos; 
		} else { 
			#define GPIO_CLR_OFFSET 0x28 
			uint32_t* output_clr = (uint32_t*) (gpio_ctr + GPIO_CLR_OFFSET + 0x4 * reg_id); *output_clr = 0x1 << pos; 
		}
	}
}

void set_gpio_pullup(void *gpio_ctr, int gpio_nr) { 
	int reg_id = gpio_nr / 32; 
	int pos = gpio_nr % 32;
	#define GPIO_PUD_OFFSET 0x94
	#define GPIO_PUDCLK_OFFSET 0x98

	uint32_t* pud_reg = (uint32_t*) (gpio_ctr + GPIO_PUD_OFFSET); 
	uint32_t* pudclk_reg = (uint32_t*) (gpio_ctr + GPIO_PUDCLK_OFFSET + 0x4 * reg_id);
	#define GPIO_PUD_PULLUP 0x2 
	*pud_reg = GPIO_PUD_PULLUP; usleep(1); 
	*pudclk_reg = (0x1 << pos); 
	usleep(1); 
	*pud_reg = 0; 
	*pudclk_reg = 0;
}
