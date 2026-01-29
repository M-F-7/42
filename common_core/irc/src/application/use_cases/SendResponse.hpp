/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SendResponse.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcastor <dcastor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:03:52 by dcastor           #+#    #+#             */
/*   Updated: 2025/09/17 11:05:25 by dcastor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IPublisher.hpp"

class SendResponse
{
private:
	IPublisher *_publisher;

public:
	SendResponse(IPublisher *publisher);

	void execute(Response &resp) const;
};
