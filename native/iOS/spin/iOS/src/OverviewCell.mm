//
//  HeaderView.m
//  spin
//
//  Created by schr3da on 29/03/15.
//
//

#import "OverviewCell.h"
#import "Helper.h"

@implementation OverviewCell

-(instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if(self != nil){
        titleL = nil;
        informationL = nil;
        descriptionL = nil;
        valueL = nil;
        
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
    CGRect frame = CGRectMake(self.frame.size.width - intent - height*1.5, (height - height * 0.5)*0.5, height*1.5, height * 0.5);
    
    [Helper releaseViewObject:&valueL];
    valueL = [[UILabel alloc]initWithFrame:frame];
    valueL.textAlignment = NSTextAlignmentRight;
    valueL.font = [UIFont fontWithName:@"HelveticaNeue-Thin" size:valueL.frame.size.height*0.9];
    valueL.textColor = [Helper getGrayColor];
    [self addSubview:valueL];
    
    [Helper releaseViewObject:&informationL];
    informationL = [[UILabel alloc]initWithFrame:CGRectMake(intent,
                                                            valueL.frame.origin.y,
                                                            self.frame.size.width,
                                                            valueL.frame.size.height * 0.65)];
    informationL.font = [UIFont fontWithName:@"HelveticaNeue-Light" size:informationL.frame.size.height*0.85];
    informationL.textColor = [Helper getGrayColor];
    [self addSubview:informationL];
    
    [Helper releaseViewObject:&descriptionL];
    descriptionL = [[UILabel alloc]initWithFrame:CGRectMake(informationL.frame.origin.x,
                                                            informationL.frame.size.height*1.55 + informationL.frame.origin.y,
                                                            informationL.frame.size.width,
                                                            informationL.frame.size.height - valueL.frame.size.height)];
    descriptionL.font = [UIFont fontWithName:@"HelveticaNeue" size:descriptionL.frame.size.height*0.85];
    descriptionL.textColor = [Helper getGrayColor];
    [self addSubview:descriptionL];
}

-(void)setValueLabelText:(NSString *)text{
    if(valueL == nil){
        valueL.text = @"";
    }
    valueL.text = (text != nil) ? text : @"";
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
    [Helper releaseViewObject:&valueL];
    [Helper releaseViewObject:&informationL];
    [Helper releaseViewObject:&descriptionL];
    [super dealloc];
}

@end
