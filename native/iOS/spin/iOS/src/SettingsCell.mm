//
//  HeaderView.m
//  spin
//
//  Created by schr3da on 29/03/15.
//
//

#import "SettingsCell.h"
#import "Helper.h"

@implementation SettingsCell

-(instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if(self != nil){
        titleL = nil;
        informationL = nil;
        descriptionL = nil;
        imageV = nil;
        
        [Helper releaseViewObject:&titleL];
        CGRect labelFrame = CGRectMake(0, 0, self.frame.size.width, self.frame.size.height);
        labelFrame.origin.x = [Helper screenBorderOffset]*0.5;
        titleL = [[UILabel alloc]initWithFrame:labelFrame];
        titleL.textColor = [Helper getGrayColor];
        titleL.font = [UIFont fontWithName:@"HelveticaNeue-Light" size:self.textLabel.font.lineHeight];
        titleL.hidden = true;
        [self addSubview:titleL];
        self.selectionStyle = UITableViewCellSelectionStyleNone;
    }
    return self;
}

-(void)addComponents{
    
    int intent = [Helper screenBorderOffset]*0.5;
    int height = [Helper largeCellHeight];
    CGRect frame = CGRectMake(intent, (height - height * 0.5)*0.5, height * 0.5, height * 0.5);
    
    [Helper releaseViewObject:&imageV];
    imageV = [[UIImageView alloc]initWithFrame:frame];
    [self addSubview:imageV];
    
    [Helper releaseViewObject:&informationL];
    informationL = [[UILabel alloc]initWithFrame:CGRectMake(imageV.frame.size.width + imageV.frame.origin.x + intent,
                                                            imageV.frame.origin.y,
                                                            self.frame.size.width - (imageV.frame.size.width + imageV.frame.origin.x + intent),
                                                            imageV.frame.size.height * 0.65)];
    informationL.font = [UIFont fontWithName:@"HelveticaNeue-Light" size:informationL.frame.size.height*0.85];
    informationL.textColor = [Helper getGrayColor];
    [self addSubview:informationL];
    
    [Helper releaseViewObject:&descriptionL];
    descriptionL = [[UILabel alloc]initWithFrame:CGRectMake(informationL.frame.origin.x,
                                                            informationL.frame.size.height*1.55 + informationL.frame.origin.y,
                                                            informationL.frame.size.width,
                                                            informationL.frame.size.height - imageV.frame.size.height)];
    descriptionL.font = [UIFont fontWithName:@"HelveticaNeue" size:descriptionL.frame.size.height*0.85];
    descriptionL.textColor = [Helper getGrayColor];
    [self addSubview:descriptionL];
}

-(void)setImageNamed:(NSString *)filename{
    if(imageV == nil){
        return;
    }
    imageV.image = [UIImage imageNamed:filename];
}

-(void)setInformationLabelText:(NSString *)text{
    if(informationL == nil){
        return;
    }
    informationL.text = (text != nil) ? text : @"";
}

-(void)setDescriptionLabelText:(NSString *)text{
    if(descriptionL == nil){
        return;
    }
    descriptionL.text = (text != nil) ? text : @"";
}

-(void)setTitleText:(NSString *)text color:(UIColor *)color{
    if(titleL == nil){
        return;
    }
    titleL.hidden = false;
    titleL.textColor = color;
    titleL.text = (text != nil) ? text : @"";
}

-(void)dealloc{
    [Helper releaseViewObject:&titleL];
    [Helper releaseViewObject:&imageV];
    [Helper releaseViewObject:&informationL];
    [Helper releaseViewObject:&descriptionL];
    [super dealloc];
}

@end
