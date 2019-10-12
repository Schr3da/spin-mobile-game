//
//  HeaderView.m
//  spin
//
//  Created by schr3da on 29/03/15.
//
//

#import "LabelButton.h"
#import "Helper.h"
#import "ImageView.h"

@implementation LabelButton

-(instancetype)initWithFrame:(CGRect)frame{
    self = [super initWithFrame:frame];
    if(self){
        imageV = nil;
        titleL = nil;
    }
    return self;
}

-(void)addLabelWithTitle:(NSString *)title andImage:(UIImage *)image{
    
    UIColor *color = [Helper getGrayColor];
    CGPoint offset = CGPointMake(0, 0);
    CGRect rect = CGRectMake(offset.x, offset.y, self.frame.size.width, self.frame.size.height*0.7);
    rect.size.width = image.size.width * rect.size.height / image.size.height;
    rect.origin.x = (self.frame.size.width - rect.size.width) *0.5;
    
    [Helper releaseViewObject:&imageV];
    imageV = [[ImageView alloc]initWithFrame:rect];
    imageV.image = image;
    imageV.userInteractionEnabled = false;
    [self addSubview:imageV];
    
    offset.y = imageV.frame.size.height + imageV.frame.origin.y;
    
    [Helper releaseViewObject:&titleL];
    titleL = [[UILabel alloc]initWithFrame:CGRectMake(0, offset.y, self.frame.size.width, self.frame.size.height - offset.y)];
    titleL.text = title;
    titleL.textAlignment = NSTextAlignmentCenter;
    titleL.textColor = color;
    titleL.font = [UIFont fontWithName:@"HelveticaNeue" size:(self.frame.size.height - offset.y)*0.8];
    titleL.userInteractionEnabled = false;
    [self addSubview:titleL];
}

-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event{
    imageV.transform = CGAffineTransformScale(imageV.transform, 1.2f, 1.2f);
    [super touchesBegan:touches withEvent:event];
}

-(void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event{
    imageV.transform = imageV.initMatrix;
    [super touchesEnded:touches withEvent:event];
}

-(NSString *)getTitle{
    return titleL.text;
}

-(void)setNewTitle:(NSString *)title andImageWithName:(NSString *)imageName{

    if(title == nil || imageName == nil || imageV == nil || titleL == nil){
        return;
    }
    imageV.image = [UIImage imageNamed:imageName];
    titleL.text = title;
    
}

-(void)dealloc{
    [Helper releaseViewObject:&imageV];
    [Helper releaseViewObject:&titleL];
    [super dealloc];
}

@end
