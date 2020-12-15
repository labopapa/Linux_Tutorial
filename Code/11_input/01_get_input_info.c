/* 
*
* 功能：获得设备信息 
* 时间：2020-12-07
*
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <linux/input.h>

/* ./01_get_input_info /dev/input/event0*/
int main(int argc, char **argv)
{
	int fd;	//设备节点
	int error;
	int len;	//读到多少数据
	int i;
	unsigned char byte;
	int bit;
	struct input_id id;
	unsigned int evbit[2];	//64位=8个字节
	char *ev_names[] = {
		"EV_SYN	"
		"EV_KEY	"
		"EV_REL	"
		"EV_ABS	"
		"EV_MSC	"
		"EV_SW	"
		"NULL   "
		"NULL   "
		"NULL   "
		"NULL   "
		"NULL   "
		"NULL   "
		"NULL   "
		"NULL   "
		"NULL   "
		"NULL   "
		"NULL   "
		"EV_LED	"
		"EV_SND	"
		"NULL   "
		"EV_REP	"
		"EV_FF	"
		"EV_PWR	"
	};	
	
	if(argc != 2)
	{
		printf("Usage: %s <dev>\n", argv[0]);
		return -1;
	}
	
	fd = open(argv[1], O_RDWR);	//打开设备节点
	if(fd < 0)
	{
		printf("open %s error\n", argv[1]);
		return -1;		
	}
	
	error = ioctl(fd, EVIOCGID, &id);	//获得设备的ID
	if(error == 0)
	{
		printf("bustype = 0x%x\n", id.bustype);
		printf("vendor  = 0x%x\n", id.vendor );
		printf("product = 0x%x\n", id.product);
		printf("version = 0x%x\n", id.version);
	}
	
	/* 获取该设备可支持的事件类型 */
	len = ioctl(fd, EVIOCGBIT(0, sizeof(evbit)), &evbit);
	if(len > 0 && len <= sizeof(evbit))
	{
		printf("suport ev type: ");
		for(i = 0; i< len; i++)
		{
			byte = ((unsigned char *) evbit)[i];
			for(bit = 0; bit < 8; bit++)
			{
				if(byte & (1<<bit))		//判断byte中哪一位等于1
				{
					printf("%s ", ev_names[i*8 + bit]);
				}
			}
		}
		printf("\n");
	}
	
	return 0;
}